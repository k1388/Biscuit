#pragma once

class Math
{
public:

    /// <summary>
    /// 使value被限制在一定范围中
    /// </summary>
    /// <param name="value">值</param>
    /// <param name="min">最小值</param>
    /// <param name="max">最大值</param>
    /// <returns></returns>
    static float Clamp(float value, float min, float max);

    const float INF = 3.40282e+38;
    const float N_INF = -3.40282e+38;
};
