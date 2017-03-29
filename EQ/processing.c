#include "processing.h"
#include "iir.h"

void calculateShelvingCoeff(float c_alpha, Int16* output)
{
	/* Your code here */
	Int16 a = c_alpha * SCALE;

	output[0] = a;
	output[1] = -SCALE;
	output[2] = SCALE - 1;
	output[3] = -a;
}

void calculatePeekCoeff(float c_alpha, float c_beta, Int16* output)
{
	/* Your code here */


	output[0] = (Int16) c_alpha*SCALE;
	output[1] = (Int16) -(c_beta *(1+c_alpha))*SCALE;
	output[2] = SCALE-1;
	output[3] = SCALE-1;
	output[4] = (Int16) -(c_beta *(1+c_alpha))*SCALE;;
	output[5] = c_alpha * SCALE;
}

Int16 shelvingHP(Int16 input, Int16* coef, Int16* z_x, Int16* z_y, Int16 k)
{
	/* Your code here */
	Int16 filtered;
	Int32 low;
	Int32 high;
	Int16 res;
	Int32 resRet;
	Int16 ret;

	filtered = first_order_IIR(input, coef, z_x, z_y);

	high = input+filtered;

	if(high > SCALE -1)
		high = SCALE - 1;
	else if(high < -SCALE)
		high = -SCALE;

	res = _smpy(k, (Int16)high);

	low = (input - filtered) >> 1;

	resRet = res + low;

	if(resRet > SCALE - 1)
		ret = SCALE - 1;
	else if (resRet < -SCALE)
		ret = -SCALE;
	else
		ret = (Int16) resRet;

	return ret;
}

Int16 shelvingLP(Int16 input, Int16* coeff, Int16* z_x, Int16* z_y, Int16 k)
{
	/* Your code here */
	Int16 filtered;
	Int32 low;
	Int32 high;
	Int16 res;
	Int32 resRet;
	Int16 ret;

	filtered = first_order_IIR(input, coeff, z_x, z_y);

	high = (input+filtered) >> 1;

	low = input - filtered;

	if(low > SCALE -1)
		low = SCALE - 1;
	else if(low < -SCALE)
		low = -SCALE;

	res = _smpy(k, (Int16)low);

	resRet = res + high;

	if(resRet > SCALE - 1)
		ret = SCALE - 1;
	else if (resRet < -SCALE)
		ret = -SCALE;
	else
		ret = (Int16) resRet;

	return ret;
}

Int16 shelvingPeek(Int16 input, Int16* coeff, Int16* z_x, Int16* z_y, Int16 k)
{
	/* Your code here */
	Int16 filtered;
		Int32 low;
		Int32 high;
		Int16 res;
		Int32 resRet;
		Int16 ret;

		filtered = second_order_IIR(input, coeff, z_x, z_y);

		high = (input+filtered) >> 1;

		low = input - filtered;

		if(low > SCALE -1)
			low = SCALE - 1;
		else if(low < -SCALE)
			low = -SCALE;

		res = _smpy(k, (Int16)low);

		resRet = res + high;

		if(resRet > SCALE - 1)
			ret = SCALE - 1;
		else if (resRet < -SCALE)
			ret = -SCALE;
		else
			ret = (Int16) resRet;

		return ret;
}
