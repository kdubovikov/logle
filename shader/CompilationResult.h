/* 
 * File:   compilation_result.h
 * Author: kdubovikov
 *
 * Created on October 24, 2014, 11:33 PM
 */
#pragma once

struct CompilationResult 
{
    enum {ERROR, OK} status;
    std::string fileName;
    std::string errorMessage;
};
