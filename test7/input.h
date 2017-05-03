double pinput(double i ,double j,double r,double A,double B)
{
	double result;
	double aa(double l,double A,double B);
	if(aa(i,A,B) > (j-127.5)*(j-127.5)) result=2*r*A*B*16384*sqrt( aa(i,A,B) - (j-127.5)*(j-127.5))/(aa(i,A,B )); //输入投影值
	else result=0;

	return result;
}


double aa(double l,double A,double B){
	return ((A*A*cos( l )*cos( l )+ B*B*sin( l )*sin( l ))*16384);
}