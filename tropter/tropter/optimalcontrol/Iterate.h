#ifndef TROPTER_OPTIMALCONTROL_ITERATE_H
#define TROPTER_OPTIMALCONTROL_ITERATE_H
// ----------------------------------------------------------------------------
// tropter: Iterate.h
// ----------------------------------------------------------------------------
// Copyright (c) 2017 tropter authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#include <Eigen/Dense>

#include <string>
#include <vector>

namespace tropter {

/// This struct holds the values the variables in an optimal control problem.
/// Iterates can be written to and read from CSV files. The file format is as
/// follows. 
/// @note Parameter values only appear in the first row, while the remaining 
/// rows in parameter columns are filled with NaNs. 
/// @note Diffuses are special variables that may not be defined at all time
/// points. For example, you may want variables defined on the points on either
/// either end of the mesh interval, or only defined on the mesh interval 
/// interior. Therefore, diffuses are real numbers at the time points where they
/// are defined and NaN everywhere else.
/// @verbatim
/// num_states=<number-of-state-variables>
/// num_controls=<number-of-control-variables>
/// num_adjuncts=<number-of-adjunct-variables>
/// num_diffuses=<number-of-diffuse-variables>
/// num_parameters=<number-of-parameter-variables>
/// time,<state-0-name>,...,<control-0-name>,...,<adjunct-0-name>,... \
///                                 <diffuse-0-name>,...,<parameter-0-name>,...
/// <#>,<#>,...,<#>,...,<#>,...,<#-or-NaN>,...,<#>,...
/// <#>,<#>,...,<#>,...,<#>,...,<#-or-NaN>,...,<NaN>,...
///  : , : ,..., : ,..., : ,...,    :     ,...,  :  ,...
/// <#>,<#>,...,<#>,...,<#>,...,<#-or-NaN>,...,<NaN>,...
/// @endverbatim
/// @ingroup optimalcontrol
// TODO rename to Variables?
struct Iterate {
    Eigen::RowVectorXd time;
    Eigen::MatrixXd states;
    Eigen::MatrixXd controls;
    Eigen::MatrixXd adjuncts;
    Eigen::MatrixXd diffuses;
    Eigen::VectorXd parameters;
    std::vector<std::string> state_names;
    std::vector<std::string> control_names;
    std::vector<std::string> adjunct_names;
    std::vector<std::string> diffuse_names;
    std::vector<std::string> parameter_names;
    /// This constructor leaves all members empty.
    Iterate() = default;
    /// True if the size of all members is 0; false otherwise.
    bool empty() const {
        return !(time.size() || states.size() || controls.size() ||
                adjuncts.size() || diffuses.size() || parameters.size() || 
                state_names.size() || control_names.size() || 
                adjunct_names.size() || diffuse_names.size() ||
                parameter_names.size());
    }
    /// Read in states and controls from a CSV file generated by calling
    /// write().
    explicit Iterate(const std::string& filepath);
    /// Linearly interpolate (upsample or downsample) the continuous variables 
    /// (i.e. states and controls) within this iterate to produce a new iterate 
    /// with a desired number of columns with equally spaced time points. This 
    /// is useful when forming an initial guess for an optimal control problem. 
    /// @returns the interpolated iterate.
    Iterate interpolate(const Eigen::VectorXd newTime) const;
    // TODO void validate(const std::string& error_message) const;
    /// Write the states and controls trajectories to a plain-text CSV file.
    virtual void write(const std::string& filepath) const;
};

/// @ingroup optimalcontrol
struct Solution : public Iterate {
    double objective;
    /// Did the solver converge?
    explicit operator bool() { return success; }
    /// Did the solver converge?
    bool success;
    /// A solver-defined string describing the return status of the optimizer.
    std::string status;
    /// Number of solver iterations at which this solution was obtained.
    int num_iterations = -1;
};

} // namespace tropter

#endif // TROPTER_OPTIMALCONTROL_ITERATE_H
