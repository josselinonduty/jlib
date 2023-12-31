/**
 * \file flags.h
 * \brief Flags
 * \author Josselin Dulongcourty
 * \version 1.0.1
 * \date 2023-12-31
 */

#ifndef __FLAGS_H__
#define __FLAGS_H__

/**
 * \enum flag_sort
 * \brief Flags for sorting
 */
typedef enum
{
    /**
     * \brief Flag a sortable type or function as unsorted
     */
    FLAG_UNSORTED,
    /**
     * \brief Flag a sortable type or function as sorted
     */
    FLAG_SORTED
} flag_sort;

#endif // __FLAGS_H__