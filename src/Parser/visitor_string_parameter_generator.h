#pragma once


//Find ${} parameters (strings inferred during compile time)
//How it works:
//0. Add a prepare visitor
//1. Use sEvalParameterRegex to find the location of all parameters.
//2. For each parameter, evaluate it
//3. If the evaluation is false, report it.
//4. If it is true, replace parameter with value.
