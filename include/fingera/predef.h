/**
 * @brief 常用的预定义
 *
 * @file predef.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-04
 */
#pragma once

#define P_IF(...) typename std::enable_if<(__VA_ARGS__)>::type* = 0
