
#include "OptimizationSolver.h"
#include "OptimizationProblem.h"

using Eigen::VectorXd;

using namespace mesh;

OptimizationSolver::OptimizationSolver(
        const AbstractOptimizationProblem& problem)
        : m_problem(problem.make_proxy()) {}

int OptimizationSolver::get_max_iterations() const
{
    return m_max_iterations;
}
void OptimizationSolver::set_max_iterations(int max_iterations)
{
    if (max_iterations < 0 && max_iterations != -1) {
        throw std::runtime_error("[mesh] max iterations is set to " +
                std::to_string(max_iterations) + ", but expected a "
                "positive number or -1.");
    }
    m_max_iterations = max_iterations;
}

double OptimizationSolver::optimize(Eigen::VectorXd& variables) const
{
    // If the user did not provide an initial guess, then we choose
    // the initial guess based on the bounds.
    if (variables.size() == 0) {
        variables = m_problem->initial_guess_from_bounds();
    } // else TODO make sure variables has the correct size.
    return optimize_impl(variables);
}