FEATURE scene.h/Impl
osg::Vec3f quaternionToDegrees(const osg::Quat &quaternion)
{
    double q0 = quaternion.x();
    double q1 = quaternion.y();
    double q2 = quaternion.z();
    double q3 = quaternion.w();
    
    //double sq0 = q0 * q0;
    double sq1 = q1 * q1;
    double sq2 = q2 * q2;
    double sq3 = q3 * q3;
    
    double term1 = 2*(q0*q1 + q2*q3);
    double term2 = 1 - 2 * (sq1 + sq2);
    double term3 = 2 * (q0*q2 - q3*q1);
    double term4 = 2 * (q0*q3 + q1*q2);
    double term5 = 1 - 2 * (sq2 + sq3);

    double z = atan2(term1, term2);
    double y = asin(term3);
    double x = atan2(term4, term5);

    osg::Vec3f result(x * 180.0 / M_PI, y * 180.0 / M_PI, z * 180.0 / M_PI);
    // Fix for X when Y = 0.
    result.x() = 180 - result.x();
    // Fix for Z when Y = 0.
    if (result.z() < 0)
    {
        result.z() = 360 + result.z();
    }
    return result;
}
