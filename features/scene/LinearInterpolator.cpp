FEATURE scene.h/Impl
//! Interpolate key:value pairs linearly.

//! You would generally use time stamps as keys to provide smooth motion interpolation.
//! NOTE requirements:
//! * the keys MUST be sorted in ascending order
//! * keyValues MUST have at least two items
class LinearInterpolator
{
    public:
        LinearInterpolator() { }

        struct KeyValue
        {
            // This constructor is necessary for operator<
            // to work for floats and KeyValues at the same time.
            KeyValue(float key): key(key), value(0) { }
            KeyValue(float key, float value): key(key), value(value) { }

            float key;
            float value;

            bool operator<(const KeyValue &other) const
            {
                return this->key < other.key;
            }
        };

        std::vector<KeyValue> keyValues;

        float valueFor(float key)
        {
            // Return edge value when requested value for keys outside
            // interpolated range.
            // First item.
            auto first = this->keyValues.front();
            if (key <= first.key)
            {
                return first.value;
            }
            // Last item.
            auto last = this->keyValues.back();
            if (key >= last.key)
            {
                return last.value;
            }

            // NOTE Interpolation code is based on this sample:
            // NOTE https://bulldozer00.com/2016/05/10/linear-interpolation-in-c/

            // Find item with the key less than requested one.
            auto it =
                std::lower_bound(
                    this->keyValues.begin(),
                    this->keyValues.end(),
                    key
                );
            // Interpolate.
            float upperX = it->key;
            float upperY = it->value;
            float lowerX = (it - 1)->key;
            float lowerY = (it - 1)->value;
            float dx = upperX - lowerX;
            float dy = upperY - lowerY;

            return lowerY + ((key - lowerX) / dx) * dy;
        }
};

