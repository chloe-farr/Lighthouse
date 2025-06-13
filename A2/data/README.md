# Dataset Overview: CESAR Surface Radiation (February 2025)

## Source Information
- **Institution**: Royal Netherlands Meteorological Institute (Koninklijk Nederlands Meteorologisch Instituut - KNMI)
- **Location**: CESAR Observatory, the Netherlands
- **Temporal Range**: February 1–28, 2025
- **Time Resolution**: ~10-minute intervals (4032 samples total)
- **Source:** https://dataplatform.knmi.nl/dataset/cesar-surface-radiation-lb1-t10-v1-0
- **Reference documentation:** https://cdn.knmi.nl/knmi/pdf/bibliotheek/knmipubTR/TR384.pdf


---

## Dimensions

| Dimension               | Size  | Description                            |
|------------------------|-------|----------------------------------------|
| `time`                 | 4032  | Timestamps of observation              |
| `day_in_time_interval` | 28    | Indexing within month                  |
| `nv`                   | 2     | Used for time bounds (e.g. start/end)  |

---

## Key Data Variables

| Variable     | Units  | Description                                                        |
|--------------|--------|--------------------------------------------------------------------|
| `SWD`        | W/m²   | Shortwave downward radiation at surface                            |
| `SWU`        | W/m²   | Shortwave upward radiation at surface                              |
| `LWD`        | W/m²   | Longwave downward radiation at surface                             |
| `LWU`        | W/m²   | Longwave upward radiation at surface                               |
| `SWDZ`       | W/m²   | Shortwave downward (not truncated to zero)                         |
| `SWUZ`       | W/m²   | Shortwave upward (not truncated to zero)                           |
| `SWDTP`      | W/m²   | Shortwave downward at top of tower                                 |
| `LWDTP`      | W/m²   | Longwave downward at top of tower                                  |
| `TSLWU`      | °C     | Surface temperature estimated from LWU                             |

Relevant variables for this project:
- `SWD`: Primary sunlight intensity indicator
- `TSLWU`: Surface brightness temperature (for atmospheric context)

---

## Preprocessing Steps

- Convert `time` to a `DatetimeIndex` for easier manipulation
- Interpolate or resample to 15-min or hourly intervals
- Normalize `SWD` for use in color temperature mapping
- Optionally filter out nighttime values using `SWD <= 0`

---

## Notes

- `valid_dates` and `time_bnds` provide metadata and can generally be ignored for visualization

---

## Tools Used
- Format: `netCDF4` (.nc)
- Parsing: [nc_converter.py](../code/nc_converter.py) script convert binary data to readable formats (currently CSV), and print metadata on the file and file attributes.
- Parsed using: `xarray`, `netCDF4`, `pandas`
