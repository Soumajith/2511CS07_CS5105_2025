import streamlit as st
import pandas as pd
import logging
import zipfile
import io
import altair as alt
from allocation_logic import allocate_students, prepare_fac_pref_stats

# Logging setup
logger = logging.getLogger('guide_allocation')
if not logger.handlers:
    handler = logging.FileHandler('app.log')
    formatter = logging.Formatter('%(asctime)s %(levelname)s %(name)s %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
logger.setLevel(logging.INFO)

st.set_page_config(page_title='Guide Allocation Platform', layout='wide')
st.title('Guide Allocation Platform')
st.markdown('### BTP/MTP Guide Allocation - Based on Numeric Preferences')

st.markdown("""
**Algorithm Explanation:**
1. **Columns after CGPA** are **faculty codes** (e.g., RH, ABM, ST).
2. **Values** under each faculty represent **preference rank** (1 = top choice).
3. Sort students by **CGPA descending**.
4. Group into batches of **n students (n = number of faculties)**.
5. Within each group, allocate based on best available preference.
""")

uploaded_file = st.file_uploader('Upload Student Preference CSV', type=['csv'])

if uploaded_file is not None:
    try:
        df = pd.read_csv(uploaded_file)

        st.subheader('Input Data Preview')
        st.dataframe(df.head(10), use_container_width=True)

        cgpa_idx = list(df.columns).index('CGPA')
        pref_cols = list(df.columns)[cgpa_idx + 1:]
        num_faculties = len(pref_cols)
        num_students = len(df)

        st.info(f"Detected **{num_students} students** and **{num_faculties} faculties**")

        num_complete_groups = num_students // num_faculties
        remaining_students = num_students % num_faculties

        if remaining_students == 0:
            st.success(f"🎯 Perfect division: {num_complete_groups} complete groups of {num_faculties}")
        else:
            st.info(f" {num_complete_groups} complete groups + {remaining_students} extra students")
            st.caption(f"→ {remaining_students} faculties get {num_complete_groups + 1} students\n→ {num_faculties - remaining_students} faculties get {num_complete_groups}")

    except Exception as e:
        st.error(f'Error reading CSV: {e}')
        st.stop()

    if st.button('Run Allocation', type='primary'):
        try:
            with st.spinner('Processing allocations...'):
                allocation_df = allocate_students(df)
                fac_stats_df = prepare_fac_pref_stats(df)

            st.success('Allocation completed successfully!')

            # Display allocation results
            col1, col2 = st.columns(2)
            with col1:
                st.subheader('Allocation Results')
                display_cols = ['Roll', 'Name', 'CGPA', 'AllocatedFaculty', 'AllocatedPrefNumber', 'CGPA_sort_rank']
                available_cols = [c for c in display_cols if c in allocation_df.columns]
                st.dataframe(allocation_df[available_cols], use_container_width=True)

            with col2:
                st.subheader('Faculty Preference Stats')
                st.dataframe(fac_stats_df, use_container_width=True)

            # Faculty allocation chart
            st.subheader("Faculty Allocation Summary")
            fac_counts = allocation_df['AllocatedFaculty'].value_counts().reset_index()
            fac_counts.columns = ['Faculty', 'AllocatedStudents']

            bar_chart = (
                alt.Chart(fac_counts)
                .mark_bar(color="#4B9CD3")
                .encode(
                    x=alt.X('Faculty', sort='-y'),
                    y='AllocatedStudents',
                    tooltip=['Faculty', 'AllocatedStudents']
                )
                .properties(height=400)
            )
            st.altair_chart(bar_chart, use_container_width=True)

            # CSVs
            csv_alloc = allocation_df.to_csv(index=False).encode('utf-8')
            csv_stats = fac_stats_df.to_csv(index=False).encode('utf-8')

            # ZIP both
            zip_buffer = io.BytesIO()
            with zipfile.ZipFile(zip_buffer, "w", zipfile.ZIP_DEFLATED) as zf:
                zf.writestr("output_btp_mtp_allocation.csv", csv_alloc)
                zf.writestr("fac_preference_count.csv", csv_stats)
            zip_buffer.seek(0)

            st.download_button(
                label="📦 Download All (ZIP)",
                data=zip_buffer,
                file_name="allocation_outputs.zip",
                mime="application/zip"
            )

        except Exception as e:
            st.error(f'Allocation failed: {e}')

else:
    st.info('Please upload a CSV file to begin allocation')
