#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

//template<typename T>
static float clamp(const float& val, const float& min, const float& max)
{
    if(val > max) 
    {
        return max;
    } 
    else if(val > min) 
    {
        return val;
    } 
    else 
    {
        return min;
    }
}

#endif // MATH_H_INCLUDED
