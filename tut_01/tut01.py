import streamlit as st
import pandas as pd
import zipfile
import re
from collections import defaultdict
from io import BytesIO

def css(path):
    try:
        with open(path, "r", encoding="utf-8") as f:
            st.markdown(f"<style>{f.read()}</style>", unsafe_allow_html=True)
    except FileNotFoundError:
        st.warning(f"⚠️ CSS file not found: {path}. Using default Streamlit style.")


def br_from_roll(roll) -> str:
    s = str(roll).strip().upper()
    m = re.match(r'^\w{4}(\w{2})', s)
    return m.group(1) if m else "UNKNOWN"

def _sizes(n: int, k: int) -> list[int]:
    q, r = divmod(n, k)
    return [q + (i < r) for i in range(k)]

def _clean_df(df: pd.DataFrame) -> pd.DataFrame:
    drop_cols = []
    for col in df.columns:
        if str(col).startswith("Unnamed"):
            drop_cols.append(col)
        elif str(col).strip().lower() == "unique":
            drop_cols.append(col)
        elif col is None or str(col) == "nan":
            drop_cols.append(col)
        elif df[col].isna().sum() == len(df):
            drop_cols.append(col)
    if drop_cols:
        df = df.drop(columns=drop_cols)
    return df


# grouping
def g_mx_br(df: pd.DataFrame, k: int) -> dict:
    out = {f"Group_{i+1}": [] for i in range(k)}
    buckets = {br: rows.to_dict("records") for br, rows in df.groupby("Branch")}
    brs = sorted(buckets.keys())
    tgt = _sizes(len(df), k)

    for i in range(k):
        g = f"Group_{i+1}"
        cap = tgt[i]
        while len(out[g]) < cap:
            moved = False
            for br in brs:
                if len(out[g]) >= cap:
                    break
                if buckets[br]:
                    out[g].append(buckets[br].pop(0))
                    moved = True
            if not moved:
                break
    return out


def g_mx_uni(df: pd.DataFrame, k: int) -> dict:
    out = {f"Group_{i+1}": [] for i in range(k)}
    tgt = _sizes(len(df), k)
    d = df.sort_values("Branch")
    stu_lst = d.to_dict("records")
    gx = 0
    for rec in stu_lst:
        gn = f"Group_{gx+1}"
        out[gn].append(rec)
        if len(out[gn]) >= tgt[gx] and gx < k - 1:
            gx += 1
    return out


def g_full_br(df: pd.DataFrame) -> dict[str, pd.DataFrame]:
    return {br: rows for br, rows in df.groupby("Branch")}


def mk_sum(groups: dict, df: pd.DataFrame) -> pd.DataFrame:
    brs = sorted(df["Branch"].unique())
    rows = []
    for gn, members in groups.items():
        row = {"Group": gn}
        tot = 0
        if members:
            gdf = pd.DataFrame(members)
            if "Branch" in gdf.columns:
                vc = gdf["Branch"].value_counts()
                vc_map = vc.to_dict()
                for br in brs:
                    v = int(vc_map.get(br, 0))
                    row[br] = v
                    tot += v
            else:
                for br in brs:
                    row[br] = 0
        else:
            for br in brs:
                row[br] = 0
        row["Total"] = tot
        rows.append(row)
    return pd.DataFrame(rows)


# zip 
def mk_pkg(df: pd.DataFrame, k: int):
    buf = BytesIO()
    with zipfile.ZipFile(buf, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        # branchwise full
        full = g_full_br(df)
        for br, data in full.items():
            zf.writestr(f"full_branchwise/{br}.csv", _clean_df(data).to_csv(index=False))

        # strategies
        bmix = g_mx_br(df, k)
        for gn, members in bmix.items():
            if members:
                zf.writestr(
                    f"group_branch_wise_mix/{gn}.csv",
                    _clean_df(pd.DataFrame(members)).to_csv(index=False),
                )

        umix = g_mx_uni(df, k)
        for gn, members in umix.items():
            if members:
                zf.writestr(
                    f"group_uniform_mix/{gn}.csv",
                    _clean_df(pd.DataFrame(members)).to_csv(index=False),
                )

        # summaries
        bsum = _clean_df(mk_sum(bmix, df))
        usum = _clean_df(mk_sum(umix, df))

        xbuf = BytesIO()
        wrote_excel = False
        for engine in ("xlsxwriter", "openpyxl", None):
            try:
                with pd.ExcelWriter(xbuf, engine=engine) as wr:
                    bsum.to_excel(wr, sheet_name="Branch_Mix", index=False)
                    usum.to_excel(wr, sheet_name="Uniform_Mix", index=False)
                zf.writestr("summary/summary.xlsx", xbuf.getvalue())
                wrote_excel = True
                break
            except Exception:
                xbuf = BytesIO()
                continue

        if not wrote_excel:
            zf.writestr("summary/Branch_Mix.csv", bsum.to_csv(index=False))
            zf.writestr("summary/Uniform_Mix.csv", usum.to_csv(index=False))

    buf.seek(0)
    return buf.getvalue(), bmix, umix, bsum, usum


def show_mx(groups: dict, title: str) -> None:
    st.markdown(f'<div class="sec-title">{title}</div>', unsafe_allow_html=True)
    tot = 0
    br_tot = defaultdict(int)
    rows = []
    for gn, members in groups.items():
        if not members:
            continue
        gdf = pd.DataFrame(members)
        sz = len(members)
        tot += sz
        dist = gdf["Branch"].value_counts().sort_index()
        info = ", ".join([f"{b}: {int(c)}" for b, c in dist.items()])
        rows.append({"Group": gn, "Size": sz, "Branch Distribution": info})
        for b, c in dist.items():
            br_tot[b] += int(c)

    if rows:
        df_a = pd.DataFrame(rows)
        st.dataframe(df_a, use_container_width=True, hide_index=True)
        c1, c2, c3, c4 = st.columns(4)
        with c1:
            st.metric("Total Students", tot)
        with c2:
            active = sum(1 for v in groups.values() if v)
            st.metric("Active Groups", active)
        with c3:
            avg = (tot // active) if active else 0
            st.metric("Avg Group Size", avg)
        with c4:
            st.metric("Branches", len(br_tot))


# main function
def main():
    st.set_page_config(page_title="Student Grouping Portal", layout="wide")
    css("styles.css")
    st.markdown(
        "<h1 style='text-align: center; font-size: 36px; font-weight: bold;'>🎓 Student Grouping System</h1>",
        unsafe_allow_html=True,
    )
    st.write("Upload student data and generate structured groups")

    # File uploader (top)
    uf = st.file_uploader(
        "Upload Data",
        type=["csv", "xlsx"],
        help="File must contain Roll, Name, Email columns",
    )

    ng = st.number_input(
        "Number of Groups",
        min_value=1,
        max_value=50,
        value=5,
        step=1,
    )

    if not uf:
        st.info("Upload a CSV or XLSX file to continue.")
        return

    try:
        if uf.name.endswith(".csv"):
            df = pd.read_csv(uf)
        else:
            df = pd.read_excel(uf)

        df = _clean_df(df)
        if "Roll" not in df.columns:
            st.error("Missing 'Roll' column in file!")
            return

        df["Branch"] = df["Roll"].apply(br_from_roll)

        st.success(f"Successfully loaded {len(df)} students from {uf.name}")

        cols_show = [c for c in ["Roll", "Name", "Email", "Branch"] if c in df.columns]

        a, b = st.columns([2, 1])
        with a:
            st.subheader("Data Overview")
            st.dataframe(df[cols_show].head(10), use_container_width=True, hide_index=True)
        with b:
            st.subheader("Branch Distribution")
            bc = df["Branch"].value_counts().sort_index()
            st.dataframe(bc.reset_index().rename(columns={"index": "Branch", "Branch": "Count"}), use_container_width=True)

        m1, m2, m3, m4 = st.columns(4)
        with m1:
            st.metric("Total Students", len(df))
        with m2:
            st.metric("Number of Groups", ng)
        with m3:
            avg = (len(df) // ng) if ng else 0
            st.metric("Avg Students/Group", avg)
        with m4:
            st.metric("Unique Branches", df["Branch"].nunique())

        if st.button("Generate Groups", type="primary", use_container_width=True):
            with st.spinner("Generating groups..."):
                zdata, bmix, umix, bsum, usum = mk_pkg(df, ng)

            st.success("Groups generated successfully!")

            t1, t2, t3, t4 = st.tabs(["Branch-wise Mix", "Uniform Mix", "Summary Tables", "Full Branch-wise"])
            with t1:
                show_mx(bmix, "Branch-wise Mix Groups")
            with t2:
                show_mx(umix, "Uniform Mix Groups")
            with t3:
                st.subheader("Branch-wise Mix Summary")
                st.dataframe(bsum, use_container_width=True, hide_index=True)
                st.subheader("Uniform Mix Summary")
                st.dataframe(usum, use_container_width=True, hide_index=True)
            with t4:
                full = g_full_br(df)
                for br, chunk in full.items():
                    with st.expander(f"Branch {br} ({len(chunk)} students)"):
                        st.dataframe(chunk[cols_show], use_container_width=True, hide_index=True)

            st.download_button(
                label="Download All Files (ZIP)",
                data=zdata,
                file_name=f"student_groups_{ng}_groups.zip",
                mime="application/zip",
                type="primary",
                use_container_width=True,
            )
    except Exception as e:
        st.error(f"Error: {str(e)}")


if __name__ == "__main__":
    main()
