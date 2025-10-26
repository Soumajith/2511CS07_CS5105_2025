import pandas as pd
import logging
from collections import defaultdict

logger = logging.getLogger('guide_allocation')


def _find_cgpa_index(df: pd.DataFrame) -> int:
    """Return index of column named exactly 'CGPA'. Case-sensitive."""
    cols = list(df.columns)
    if 'CGPA' not in cols:
        raise ValueError("Input CSV must contain a column named 'CGPA' (case-sensitive).")
    return cols.index('CGPA')

def allocate_students(df: pd.DataFrame) -> pd.DataFrame:
    """
    Allocates faculty based on numeric preference columns.
    - Columns after CGPA are faculty codes.
    - Values = numeric preference rank (1 = top choice).
    - Sorted by CGPA (descending).
    - Allocation done in groups of n (n = number of faculties).
    """

    df = df.copy()
    cgpa_idx = _find_cgpa_index(df)
    pref_cols = list(df.columns)[cgpa_idx + 1:]
    n = len(pref_cols)
    num_students = len(df)

    # Sort by CGPA descending
    df['__CGPA_numeric'] = pd.to_numeric(df['CGPA'], errors='coerce').fillna(-1e9)
    df_sorted = df.sort_values(by='__CGPA_numeric', ascending=False).reset_index(drop=True)

    roll_to_faculty = {}

    # Group allocation
    for group_start in range(0, num_students, n):
        group_end = min(group_start + n, num_students)
        group_df = df_sorted.iloc[group_start:group_end]
        taken = set()

        for _, row in group_df.iterrows():
            roll = row.get('Roll', f"row_{_}")
            prefs = []

            for fac in pref_cols:
                val = pd.to_numeric(row[fac], errors='coerce')
                if pd.notna(val):
                    prefs.append((fac, int(val)))

            prefs.sort(key=lambda x: x[1])

            allocated_fac = None
            for fac, _ in prefs:
                if fac not in taken:
                    allocated_fac = fac
                    taken.add(fac)
                    break

            roll_to_faculty[roll] = allocated_fac if allocated_fac else 'UNALLOCATED'

    # Final clean output
    df['AllocatedFaculty'] = df['Roll'].map(roll_to_faculty)
    output_cols = ['Roll', 'Name', 'Email', 'CGPA', 'AllocatedFaculty']
    return df[output_cols]


def prepare_fac_pref_stats(df: pd.DataFrame) -> pd.DataFrame:
    """
    For each faculty (column), count how many students ranked it as Pref1, Pref2, ...
    """
    cgpa_idx = _find_cgpa_index(df)
    pref_cols = list(df.columns)[cgpa_idx + 1:]

    # Find the maximum preference rank value
    max_pref = int(df[pref_cols].max().max())

    fac_pref_counts = defaultdict(lambda: [0] * max_pref)

    for _, row in df.iterrows():
        for fac in pref_cols:
            val = pd.to_numeric(row[fac], errors='coerce')
            if pd.notna(val) and 1 <= int(val) <= max_pref:
                fac_pref_counts[fac][int(val) - 1] += 1

    # Build DataFrame
    data = []
    for fac, counts in sorted(fac_pref_counts.items()):
        entry = {'Faculty': fac}
        for i, c in enumerate(counts, start=1):
            entry[f'Pref {i}'] = c
        data.append(entry)

    return pd.DataFrame(data)
