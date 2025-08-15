# Fetches data stored by C API #
values = globals().get('values')

# Types that can be written to the CPP file #
allowed_types = (int, float, str)

# Dictionary to store filtered values by type #
type_dicts = { t.__name__: {} for t in allowed_types }

for key, value in values.items():
    # Skip 'hidden' items #
    if key[:2] == "__":
        continue

    # Skip invalid types #
    if not isinstance(value, allowed_types):
        print(f"Invalid type: {type(value).__name__} for key '{key}'")

    # Adds value to correct dictionary #
    type_name = type(value).__name__
    type_dicts[type_name][key] = value

# Print results (temporary) #
for t, d in type_dicts.items():
    print(f"{t}: {d}")
