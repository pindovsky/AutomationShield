%   EMPC MEMORY ESTIMATION
%
%   This example reads requires an explicit controller object generated by
%   the Multi-Parametric Toolbox of Kvasnica et al. (mpt3.org) and outputs
%   the number of bytes required for storage in the memory. The computation
%   does not contain anything, but the storage requirements of the
%   polyhedra and the associated control laws, e.g. the real memory
%   requirement will contain the rest of your control application

%   This code is part of the AutomationShield hardware and software
%   ecosystem. Visit http://www.automationshield.com for more
%   details. This code is licensed under a Creative Commons
%   Attribution-NonCommercial 4.0 International License.
%
%   If you have found any use of this code, please cite our work in your
%   academic publications, such as theses, conference articles or journal
%   papers. A list of publications connected to the AutomationShield
%   project is available at: 
%   https://github.com/gergelytakacs/AutomationShield/wiki/Publications
%
%   Created by:       Gergely Tak�cs and Martin Gulan. 
%   Created on:       9.11.2020
%   Last updated by:  Gergely Tak�cs
%   Last update on:   9.11.2020


function memory = empcMemory(ectrl, numeric)

if numeric == 'float'
    bytes = 4;                 % 4 bytes for a single precision floating point number
elseif numeric == 'double'
    bytes = 8;                 % 8 bytes for a single precision floating point number
else
    error('Numeric type undefined.')
end    
floats = 0;                    % Initialize zero numbers
for i = 1:ectrl.optimizer.Num  % Sweep through all partitions
        floats = floats + prod(size(ectrl.optimizer.Set(i).A));
        floats = floats + prod(size(ectrl.optimizer.Set(i).b));
        floats = floats + prod(size(ectrl.optimizer.Set(i).Functions('primal').F));
        floats = floats + prod(size(ectrl.optimizer.Set(i).Functions('primal').g));
end
memory = (floats*bytes);      % Number of floating point numbers*number of bytes in each of them