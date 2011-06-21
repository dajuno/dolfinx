// Copyright (C) 2008-2011 Anders Logg and Garth N. Wells
//
// This file is part of DOLFIN.
//
// DOLFIN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DOLFIN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
//
// Modified by Marie E. Rognes, 2011.
//
// First added:  2011-01-14 (2008-12-26 as VariationalProblem)
// Last changed: 2011-01-14

#ifndef __LINEAR_VARIATIONAL_SOLVER_H
#define __LINEAR_VARIATIONAL_SOLVER_H

#include <dolfin/la/LUSolver.h>
#include <dolfin/la/KrylovSolver.h>

namespace dolfin
{

  class Function;
  class VariationalProblem;
  class Parameters;

  /// This class implements a solver for linear variational problems.

  class LinearVariationalSolver : public Variable
  {
  public:

    /// Create linear variational solver
    LinearVariationalSolver(const Form& a,
                            const Form& L,
                            Function& u,
                            std::vector<const BoundaryCondition*> bcs);

    /// Create linear variational solver
    LinearVariationalSolver(boost::shared_ptr<const Form> a,
                            boost::shared_ptr<const Form> L,
                            boost::shared_ptr<Function> u,
                            std::vector<boost::shared_ptr<const BoundaryCondition> > bcs);

    /// Solve variational problem
    void solve();

    /// Default parameter values
    static Parameters default_parameters()
    {
      Parameters p("linear_variational_solver");

      p.add("linear_solver", "lu");
      p.add("preconditioner", "default");
      p.add("symmetric", false);
      p.add("reset_jacobian", true);

      p.add("print_rhs", false);
      p.add("print_matrix", false);

      p.add(LUSolver::default_parameters());
      p.add(KrylovSolver::default_parameters());

      return p;
    }

  private:

    // Check forms
    void check_forms() const;

    // The bilinear form
    boost::shared_ptr<const Form> a;

    // The linear form
    boost::shared_ptr<const Form> L;

    // The solution
    boost::shared_ptr<Function> u;

    // The boundary conditions
    std::vector<boost::shared_ptr<const BoundaryCondition> > bcs;

  };

}

#endif
