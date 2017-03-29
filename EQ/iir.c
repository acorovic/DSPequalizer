#include "iir.h"

/**************************************
 * IIR filtar prvog reda
 *
 * input - ulazni odbirak
 * coefficients - koeficijenti [a0 a1 b0 b1]
 * z_x - memorija za ulazne odbirke (niz duzine 2)
 * z_y - memorija za izlazne odbirke (niz duzine 2)
 *
 * povratna vrednost - izlazni odbirak
 *
 **************************************/

Int16 first_order_IIR( Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y )
{
	Int32 temp;

	z_x[0] = input; /* Copy input to x[0] */

    temp = ( (Int32) coefficients[0] * z_x[0]) ;   /* B0 * x(n)     */
    temp += ( (Int32) coefficients[1] * z_x[1]);    /* B1 * x(n-1) */
    temp -= ( (Int32) coefficients[3] * z_y[1]);    /* A1 * y(n-1) */

     /* Divide temp by coefficients[A0] to remove fractional part */
     temp >>= 15;

     z_y[0] = (Int16) ( temp );

     /* Shuffle values along one place for next time */

     z_y[1] = z_y[0];   /* y(n-1) = y(n)   */
     z_x[1] = z_x[0];   /* x(n-1) = x(n)   */

     return ( (Int16) temp );
}

/**************************************
* IIR filtar drugog reda
*
* input - ulazni odbirak
* coefficients - koeficijenti [a0 a1/2 a2 b0 b1/2 b2]
* z_x - memorija za ulazne odbirke (niz duzine 3)
* z_y - memorija za izlazne odbirke (niz duzine 3)
*
* povratna vrednost - izlazni odbirak
*
* NAPOMENA: Koeficijenti b1 i a1 se nalaze u opsegu [-2, 2),
* stoga se prosledjuje polovina njihove vrednosti kako bi
* mogli biti prezentovani u 1.31 prezentaciji brojeva u
* nepokretnom zarezu
*************************************/

Int16 second_order_IIR( Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y)
{
	Int32 temp;

    z_x[0] = input; /* Copy input to x[0] */

    temp =  ( (Int32) coefficients[0] * z_x[0]) ;   /* B0 * x(n)     */
    temp += ( (Int32) coefficients[1] * z_x[1]);    /* B1/2 * x(n-1) */
    temp += ( (Int32) coefficients[1] * z_x[1]);    /* B1/2 * x(n-1) */
    temp += ( (Int32) coefficients[2] * z_x[2]);    /* B2 * x(n-2)   */
    temp -= ( (Int32) coefficients[4] * z_y[1]);    /* A1/2 * y(n-1) */
    temp -= ( (Int32) coefficients[4] * z_y[1]);    /* A1/2 * y(n-1) */
    temp -= ( (Int32) coefficients[5] * z_y[2]);    /* A2 * y(n-2)   */

    /* Divide temp by coefficients[A0] to remove fractional part */
    temp >>= 15;

    z_y[0] = (Int16) ( temp );

    /* Shuffle values along one place for next time */

    z_y[2] = z_y[1];   /* y(n-2) = y(n-1) */
    z_y[1] = z_y[0];   /* y(n-1) = y(n)   */
    z_x[2] = z_x[1];   /* x(n-2) = x(n-1) */
    z_x[1] = z_x[0];   /* x(n-1) = x(n)   */

 return ( (Int16) temp );
}
