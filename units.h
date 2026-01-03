#ifndef UNITS_H
#define UNITS_H

// Distance
#define METERS_PER_KM 1000.0
#define METERS_PER_AU 1.495978707e11

// Time
#define SECONDS_PER_DAY 86400.0
#define SECONDS_PER_HOUR 3600.0
#define SECONDS_PER_YEAR 31557600.0

// Gravity
#define G_SI 6.67430e-11

// Converted gravity constant for AU units
#define G_AU (G_SI / (METERS_PER_AU * METERS_PER_AU * METERS_PER_AU))

static inline double km_to_au(double km) {
    return (km * METERS_PER_KM) / METERS_PER_AU;
}

static inline double days(double d) {
    return d * SECONDS_PER_DAY;
}

static inline double years(double y) {
    return y * SECONDS_PER_YEAR;
}

static inline double kms_to_aus(double km_s) {
    return (km_s * METERS_PER_KM) / METERS_PER_AU;
}

#endif

