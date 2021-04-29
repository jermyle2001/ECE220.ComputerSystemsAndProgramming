//Partners: bgin2 jeremyl6, tmshu2

#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber() //Empty constructor
{
    /* Your code here */
    real_component = 0.0;
    imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component) //Create constructor
{
    /* Your code here */
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other ) //Copy constructor
{
    /* Your code here */
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
}

void ComplexNumber::set_real_component (double rval) 
{
    /* Your code here */
    real_component = rval;
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    imaginary_component = rval;
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return sqrt(real_component * real_component + imaginary_component * imaginary_component);
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return calculate_phase(real_component, imaginary_component);
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg) //Add two complex number together
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)(c + id) = (ac-bd) + i(ad+bc)
    //(ac-bd)
    real_temp = (real_component * arg.get_real_component()) - (imaginary_component * arg.get_imaginary_component());
    //(ad+bc)
    imag_temp = (real_component * arg.get_imaginary_component()) + (imaginary_component * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)/(c + id) = (ac+bd)/(c^2 + d^2), (bc-ad)/(c^2+d^2)
    //(ac+bd)/(c^2 + d^2) RealComponent
    real_temp = (real_component * arg.get_real_component() + imaginary_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    //(bc-ad)/(c^2+d^2)
    imag_temp = (imaginary_component * arg.get_real_component() - real_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg) 
{
    /* Your code here */
	return ComplexNumber(real_component + arg.get_real_component(), imaginary_component); //Only real number changes, keep imaginary_component
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component - arg.get_real_component(), imaginary_component); //Only real number changes, keep imaginary_component
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    //Identical formula, except imaginary component doesn't exist in real number, so substitute zero
	double real_temp = 0.0; 
    double imag_temp = 0.0;
    //(a + ib)(c + id) = (ac-bd) + i(ad+bc)
    //(ac-bd)
    real_temp = (real_component * arg.get_real_component()) - (imaginary_component * 0);
    //(ad+bc)
    imag_temp = (real_component * 0) + (imaginary_component * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    //Idenitcal formula, except imaginary component doesn't exixst in real number, so substitute zero
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)/(c + id) = (ac+bd)/(c^2 + d^2), (bc-ad)/(c^2+d^2)
    //(ac+bd)/(c^2 + d^2) RealComponent
    real_temp = (real_component * arg.get_real_component() + imaginary_component * 0) / (0 * 0 + arg.get_real_component() * arg.get_real_component());
    //(bc-ad)/(c^2+d^2)
    imag_temp = (imaginary_component * arg.get_real_component() - real_component * 0) / (0 * 0 + arg.get_real_component() * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg) //Only imaginary number changes, keep real_component
    { 
    /* Your code here */
    return ComplexNumber(real_component + 0, imaginary_component + arg.get_imaginary_component());
    }

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg) //Only imaginary number changes, keep real_component
{
    /* Your code here */
	return ComplexNumber(real_component - 0, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    //Identical formula, except real component doesn't exist, so substitute zero
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)(c + id) = (ac-bd) + i(ad+bc)
    //(ac-bd)
    real_temp = (real_component * 0) - (imaginary_component * arg.get_imaginary_component());
    //(ad+bc)
    imag_temp = (real_component * arg.get_imaginary_component()) + (imaginary_component * 0);
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    //Identical formula, except real component doesn't exist, so substitute zero
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)/(c + id) = (ac+bd)/(c^2 + d^2), (bc-ad)/(c^2+d^2)
    //(ac+bd)/(c^2 + d^2) RealComponent
    real_temp = (real_component * 0 + imaginary_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + 0 * 0);
    //(bc-ad)/(c^2+d^2)
    imag_temp = (imaginary_component * 0 - real_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + 0 * 0);
    return ComplexNumber(real_temp, imag_temp);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}
