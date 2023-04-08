// floats break down around the same time as fixed point (1e11f: 99999997952.000000)
// except fixed point always works across space and time
struct fixed32 {
    u32 value;
};
