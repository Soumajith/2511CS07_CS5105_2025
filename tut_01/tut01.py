import streamlit as st
import pandas as pd
import zipfile
import re
from io import BytesIO
from typing import Dict, List, Any
from itertools import chain, zip_longest

class GroupingStrategy:

    def _partition_sizes(self, item_count: int, group_count: int) -> List[int]:
        if group_count <= 0: return []
        base, rem = divmod(item_count, group_count)
        return [base + 1 if i < rem else base for i in range(group_count)]

    def create(self, student_df: pd.DataFrame, num_groups: int) -> Dict[str, List[Dict]]:
        raise NotImplementedError("Each strategy must implement its own create method.")

class DiverseMixStrategy(GroupingStrategy):

    def create(self, student_df: pd.DataFrame, num_groups: int) -> Dict[str, List[Dict]]:
        groups = {f'Group_{i+1}': [] for i in range(num_groups)}
        sizes = self._partition_sizes(len(student_df), num_groups)

        branch_lists = [
            list(records.to_dict('records'))
            for _, records in student_df.groupby('Branch')
        ]
        
        interleaved_students = list(
            chain.from_iterable(
                filter(None, student) for student in zip_longest(*branch_lists)
            )
        )
        
        student_idx = 0
        for i in range(num_groups):
            group_name = f'Group_{i+1}'
            num_to_add = sizes[i]
            groups[group_name] = interleaved_students[student_idx : student_idx + num_to_add]
            student_idx += num_to_add
            
        return groups

class SequentialFillStrategy(GroupingStrategy):

    def create(self, student_df: pd.DataFrame, num_groups: int) -> Dict[str, List[Dict]]:
        groups = {f'Group_{i+1}': [] for i in range(num_groups)}
        sizes = self._partition_sizes(len(student_df), num_groups)
        
        sorted_students = student_df.sort_values('Branch').to_dict('records')
        
        student_idx = 0
        for i in range(num_groups):
            group_name = f'Group_{i+1}'
            num_to_add = sizes[i]
            groups[group_name] = sorted_students[student_idx : student_idx + num_to_add]
            student_idx += num_to_add

        return groups

class ReportGenerator:
    
    def __init__(self, student_df: pd.DataFrame):
        self.student_df = student_df
        self.all_branches = sorted(student_df['Branch'].unique())

    def _build_summary(self, groups: Dict) -> pd.DataFrame:
        summary_data = []
        for name, members in groups.items():
            row = {'Group': name, 'Total': len(members)}
            if members:
                counts = pd.Series(m['Branch'] for m in members).value_counts()
                row.update({b: counts.get(b, 0) for b in self.all_branches})
            else:
                row.update({b: 0 for b in self.all_branches})
            summary_data.append(row)
        
        df = pd.DataFrame(summary_data)
        
        if 'Total' in df.columns:
            cols = [col for col in df.columns if col != 'Total'] + ['Total']
            df = df[cols]
            
        return df

    def create_zip_archive(self, diverse_groups: Dict, sequential_groups: Dict) -> bytes:
        buffer = BytesIO()
        with zipfile.ZipFile(buffer, 'w', zipfile.ZIP_DEFLATED) as zf:
            
            # Package diverse mix groups
            for name, members in diverse_groups.items():
                if members:
                    zf.writestr(f'group_branch_wise_mix/{name}.csv', pd.DataFrame(members).to_csv(index=False))

            # Package sequential fill groups
            for name, members in sequential_groups.items():
                if members:
                    zf.writestr(f'group_uniform_mix/{name}.csv', pd.DataFrame(members).to_csv(index=False))

            # Package full branchwise lists
            for branch, data in self.student_df.groupby('Branch'):
                zf.writestr(f'full_branchwise/{branch}.csv', data.to_csv(index=False))

            # Create and package Excel summary
            summary_diverse = self._build_summary(diverse_groups)
            summary_sequential = self._build_summary(sequential_groups)

            excel_buffer = BytesIO()
            with pd.ExcelWriter(excel_buffer, engine='openpyxl') as writer:
                summary_diverse.to_excel(writer, sheet_name='Branch_Mix_Summary', index=False)
                summary_sequential.to_excel(writer, sheet_name='Uniform_Mix_Summary', index=False)
            zf.writestr('summary.xlsx', excel_buffer.getvalue())

        buffer.seek(0)
        return buffer.getvalue()

class AppManager:

    def __init__(self):
        st.set_page_config(page_title="Student Grouping Engine", layout="wide")
        if 'results' not in st.session_state:
            st.session_state.results = None

    def _load_data(self, uploaded_file) -> pd.DataFrame:
        df = pd.read_csv(uploaded_file) if uploaded_file.name.endswith('.csv') else pd.read_excel(uploaded_file)
        
        # --- Cleaning Logic ---
        df = df.dropna(axis=1, how='all')
        
        cols_to_drop = [
            col for col in df.columns 
            if str(col).startswith('Unnamed') or str(col).strip().lower() == 'unique'
        ]
        df = df.drop(columns=cols_to_drop)

        if 'Roll' not in df.columns:
            raise ValueError("Input file must contain a 'Roll' column.")
        df['Branch'] = df['Roll'].apply(lambda r: re.match(r'^\w{4}(\w{2})', str(r).strip().upper()).group(1) if re.match(r'^\w{4}(\w{2})', str(r).strip().upper()) else "UNKNOWN")
        return df

    def _render_data_preview(self, df: pd.DataFrame):
        st.subheader("Data Preview")
        st.dataframe(df.head(), use_container_width=True, hide_index=True)
        st.subheader("Branch Distribution")
        st.dataframe(df['Branch'].value_counts(), use_container_width=True)

    def _render_results(self, results: Dict):
        st.success("Group generation complete!")
        
        tabs = st.tabs(["Branch Mix", "Uniform Mix", "Branchwise", "Summaries"])
        
        with tabs[0]:
            self._display_group_details(results['diverse_groups'], "Branch Mix Group Details")
        with tabs[1]:
            self._display_group_details(results['sequential_groups'], "Uniform Mix Group Details")
        with tabs[2]:
            st.subheader("Complete Student Lists by Branch")
            for branch, data in results['df'].groupby('Branch'):
                with st.expander(f"Branch: {branch} ({len(data)} students)"):
                    st.dataframe(data, use_container_width=True, hide_index=True)
        with tabs[3]:
            st.subheader("Branch Mix Summary")
            st.dataframe(results['diverse_summary'], use_container_width=True, hide_index=True)
            st.subheader("Uniform Mix Summary")
            st.dataframe(results['sequential_summary'], use_container_width=True, hide_index=True)


    def _display_group_details(self, groups: Dict, title: str):
        st.subheader(title)
        rows = []
        for name, members in groups.items():
            if not members: continue
            counts = pd.Series([s['Branch'] for s in members]).value_counts().sort_index()
            dist_str = ', '.join([f"{b}: {c}" for b, c in counts.items()])
            rows.append({'Group': name, 'Size': len(members), 'Distribution': dist_str})
        if rows:
            st.dataframe(pd.DataFrame(rows), use_container_width=True, hide_index=True)

    def run(self):
        st.title("Student Grouping Engine")
        
        uploaded_file = st.file_uploader("Upload Student Roster", type=['csv', 'xlsx'])
        num_groups = st.number_input("Number of Groups to Create", min_value=1, max_value=100, value=5)

        if not uploaded_file:
            st.info("Upload a student data file to begin.")
            return

        try:
            student_df = self._load_data(uploaded_file)
            self._render_data_preview(student_df)

            if st.button("Generate Groups & Download Package", type="primary", use_container_width=True):
                with st.spinner("Generating all reports and packages..."):
                    # Generate groups and summaries once
                    diverse_groups = DiverseMixStrategy().create(student_df, num_groups)
                    sequential_groups = SequentialFillStrategy().create(student_df, num_groups)
                    
                    reporter = ReportGenerator(student_df)
                    diverse_summary = reporter._build_summary(diverse_groups)
                    sequential_summary = reporter._build_summary(sequential_groups)

                    zip_bytes = reporter.create_zip_archive(diverse_groups, sequential_groups)
                    
                    # Store all results in session state
                    st.session_state.results = {
                        'zip': zip_bytes, 
                        'df': student_df,
                        'diverse_groups': diverse_groups,
                        'sequential_groups': sequential_groups,
                        'diverse_summary': diverse_summary,
                        'sequential_summary': sequential_summary
                    }

            if st.session_state.results:
                self._render_results(st.session_state.results)
                st.download_button(
                    label="Download Full Package (.zip)",
                    data=st.session_state.results['zip'],
                    file_name=f"student_groups_{num_groups}_groups.zip",
                    mime="application/zip",
                    use_container_width=True
                )

        except Exception as e:
            st.error(f"An error occurred: {e}")

if __name__ == "__main__":
    app = AppManager()
    app.run()