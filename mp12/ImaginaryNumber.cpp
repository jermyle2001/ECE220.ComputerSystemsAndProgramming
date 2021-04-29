//Partners: bgin2 jeremyl6, tmshu2

#include "ImaginaryNumber.h"
#include "helper.h"

//Create family of constructors
ImaginaryNumber::ImaginaryNumber() //Empty constructor
{
    /* Your code here */
    imaginary_component = 0.0;
}

ImaginaryNumber::ImaginaryNumber(double rval) //Complete constructor
{
    /* Your code here */
    imaginary_component = rval;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other ) //Copy constructor to var
{
    /* Your code here */
    imaginary_component = other.get_imaginary_component();
}

void ImaginaryNumber::set_imaginary_component (double rval) //Set imaginary component of variable
{
    /* Your code here */
    imaginary_component = rval; //Sets imaginary_component to rval
}

double ImaginaryNumber::get_imaginary_component() const //Returns value of imaginary_component
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{ //Returns magnitude of imaginary_component
    /* Your code here */
    return abs(imaginary_component); //No real component exists
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{ //Returns phase of imaginary_component through derived component
    /* Your code here */
    return calculate_phase(0,imaginary_component);
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(-1 * imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(imaginary_component / arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg) //Components are separate, so just throw into ComplexNumber
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg) //Components are separate, so just throw into ComplexNumber
{
    /* Your code here */
    return ComplexNumber(-1 * arg.get_real_component(), imaginary_component); 
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg) //RealNumber treated as a scalar, compute as such
{
    /* Your code here */
    return ImaginaryNumber(arg.get_real_component() * imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg) //RealNumber treated as a scalar, compute as such
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component / arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1 * arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    //Identical formula, except real component doesn't exist, so substitute zero
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)(c + id) = (ac-bd) + i(ad+bc)
    //(ac-bd)
    real_temp = (0 * arg.get_real_component()) - (imaginary_component * arg.get_imaginary_component());
    //(ad+bc)
    imag_temp = (0 * arg.get_imaginary_component()) + (imaginary_component * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    //Identical formula, except real component doesn't exist, so substitute zero
    double real_temp = 0.0;
    double imag_temp = 0.0;
    //(a + ib)/(c + id) = (ac+bd)/(c^2 + d^2), (bc-ad)/(c^2+d^2)
    //(ac+bd)/(c^2 + d^2) RealComponent
    real_temp = (0 * arg.get_real_component() + imaginary_component * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    //(bc-ad)/(c^2+d^2)
    imag_temp = (imaginary_component * arg.get_real_component() - 0 * arg.get_imaginary_component()) / (arg.get_imaginary_component() * arg.get_imaginary_component() + arg.get_real_component() * arg.get_real_component());
    return ComplexNumber(real_temp, imag_temp);
    return ComplexNumber();
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}
