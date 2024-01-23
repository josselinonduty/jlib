#ifndef __SWAP_H__
#define __SWAP_H__

#include "base/generic.h"

/**
 * \brief Swap two elements by reference.
 * \param a A pointer to the first element.
 * \param b A pointer to the second element.
 *
 * \post EINVAL if either a or b is NULL.
 * \example
 * \code{.c}
 * int a = 1;
 * any pa = &a;
 * int b = 2;
 * any pb = &b;
 *
 * swap(&pa, &pb);
 * // a = 2, b = 1
 * \endcode
 */
void swap(any *a, any *b);

#endif // __SWAP_H__