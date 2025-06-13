"""
THIS SCRIPT:
prints .nc metadata (Network Common Data Form)
Converts binary .nc into a readable CSV format
Params: .nc file path, variables to extract
Outputs: .csv
"""
import xarray as xr
import os
import sys
import pandas as pd

# Usage: python nc_converter.py path/to/file.nc var1,var2,var3
if len(sys.argv) < 3:
    print("Use: python nc_converter.py <path_to_nc_file> <comma_separated_variables>")
    sys.exit(1)

nc_path = sys.argv[1]
var_names = sys.argv[2].split(',')

# Load dataset
ds = xr.open_dataset(nc_path)

# Check variables exist
missing = [v for v in var_names if v not in ds.variables]
if missing:
    print(f"Variables not found and skipped: {', '.join(missing)}")
    var_names = [v for v in var_names if v in ds.variables]

if not var_names:
    print("No valid variables to extract.")
    sys.exit(1)

# Convert selected variables to a DataFrame (they must share coordinates like 'time')
df = ds[var_names].to_dataframe().reset_index()

# Prepare output directory
csv_dir = os.path.join(os.path.dirname(nc_path), "../data/", "csv")
os.makedirs(csv_dir, exist_ok=True)

# Build filename
var_suffix = "__" + "_".join(var_names)
csv_name = os.path.splitext(os.path.basename(nc_path))[0] + f"{var_suffix}.csv"
csv_path = os.path.join(csv_dir, csv_name)

# Save
df.to_csv(csv_path, index=False)
print(f"Saved combined CSV to {csv_path}")