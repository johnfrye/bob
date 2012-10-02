/**
 * @file machine/python/gmm.cc
 * @date Tue Jul 26 15:11:33 2011 +0200
 * @author Laurent El Shafey <Laurent.El-Shafey@idiap.ch>
 *
 * Copyright (C) 2011-2012 Idiap Research Institute, Martigny, Switzerland
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/python.hpp>
#include <boost/concept_check.hpp>
#include "bob/machine/GMMStats.h"
#include "bob/machine/GMMMachine.h"
#include "bob/machine/GMMLLRMachine.h"
#include <blitz/array.h>

#include "bob/core/python/ndarray.h"

using namespace boost::python;
namespace io = bob::io;
namespace mach = bob::machine;
namespace bp = bob::python;
namespace ca = bob::core::array;


static object py_gmmstats_getN(mach::GMMStats& s) {
  bp::ndarray n(ca::t_float64, s.n.extent(0));
  blitz::Array<double,1> n_ = n.bz<double,1>();
  n_ = s.n;
  return n.self();
}
 
static void py_gmmstats_setN(mach::GMMStats& s, bp::const_ndarray n) {
  const ca::typeinfo& info = n.type();
  if(info.dtype != ca::t_float64 || info.nd != 1)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  s.n = n.bz<double,1>();
}

static object py_gmmstats_getSumpx(mach::GMMStats& s) {
  bp::ndarray sumpx(ca::t_float64, s.sumPx.extent(0), s.sumPx.extent(1));
  blitz::Array<double,2> sumpx_ = sumpx.bz<double,2>();
  sumpx_ = s.sumPx;
  return sumpx.self();
}
 
static void py_gmmstats_setSumpx(mach::GMMStats& s, bp::const_ndarray sumpx) {
  const ca::typeinfo& info = sumpx.type();
  if(info.dtype != ca::t_float64 || info.nd != 2)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  s.sumPx = sumpx.bz<double,2>();
}
 
static object py_gmmstats_getSumpxx(mach::GMMStats& s) {
  bp::ndarray sumpxx(ca::t_float64, s.sumPxx.extent(0), s.sumPxx.extent(1));
  blitz::Array<double,2> sumpxx_ = sumpxx.bz<double,2>();
  sumpxx_ = s.sumPxx;
  return sumpxx.self();
}
 
static void py_gmmstats_setSumpxx(mach::GMMStats& s, bp::const_ndarray sumpxx) {
  const ca::typeinfo& info = sumpxx.type();
  if(info.dtype != ca::t_float64 || info.nd != 2)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  s.sumPxx = sumpxx.bz<double,2>();
}


static object py_gmmmachine_getWeights(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  bp::ndarray weights(ca::t_float64, n_gaussians);
  blitz::Array<double,1> weights_ = weights.bz<double,1>();
  weights_ = machine.getWeights();
  return weights.self();
}

static void py_gmmmachine_setWeights(mach::GMMMachine& machine, bp::const_ndarray weights) {
  const ca::typeinfo& info = weights.type();
  if(info.dtype != ca::t_float64 || info.nd != 1)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setWeights(weights.bz<double,1>());
}

static object py_gmmmachine_getMeans(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  size_t n_inputs = machine.getNInputs();
  bp::ndarray means(ca::t_float64, n_gaussians, n_inputs);
  blitz::Array<double,2> means_ = means.bz<double,2>();
  machine.getMeans(means_);
  return means.self();
}

static void py_gmmmachine_setMeans(mach::GMMMachine& machine, bp::const_ndarray means) {
  const ca::typeinfo& info = means.type();
  if(info.dtype != ca::t_float64 || info.nd != 2)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setMeans(means.bz<double,2>());
}

static object py_gmmmachine_getMeanSupervector(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  size_t n_inputs = machine.getNInputs();
  bp::ndarray vec(ca::t_float64, n_gaussians * n_inputs);
  blitz::Array<double,1> vec_ = vec.bz<double,1>();
  vec_ = machine.getMeanSupervector();
  return vec.self();
}

static void py_gmmmachine_setMeanSupervector(mach::GMMMachine& machine, bp::const_ndarray vec) {
  const ca::typeinfo& info = vec.type();
  if(info.dtype != ca::t_float64 || info.nd != 1)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setMeanSupervector(vec.bz<double,1>());
}

static object py_gmmmachine_getVariances(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  size_t n_inputs = machine.getNInputs();
  bp::ndarray variances(ca::t_float64, n_gaussians, n_inputs);
  blitz::Array<double,2> variances_ = variances.bz<double,2>();
  machine.getVariances(variances_);
  return variances.self();
}

static void py_gmmmachine_setVariances(mach::GMMMachine& machine, bp::const_ndarray variances) {
  const ca::typeinfo& info = variances.type();
  if(info.dtype != ca::t_float64 || info.nd != 2)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setVariances(variances.bz<double,2>());
}

static object py_gmmmachine_getVarianceSupervector(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  size_t n_inputs = machine.getNInputs();
  bp::ndarray vec(ca::t_float64, n_gaussians * n_inputs);
  blitz::Array<double,1> vec_ = vec.bz<double,1>();
  vec_ = machine.getVarianceSupervector();
  return vec.self();
}

static void py_gmmmachine_setVarianceSupervector(mach::GMMMachine& machine, bp::const_ndarray vec) {
  const ca::typeinfo& info = vec.type();
  if(info.dtype != ca::t_float64 || info.nd != 1)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setVarianceSupervector(vec.bz<double,1>());
}

static object py_gmmmachine_getVarianceThresholds(const mach::GMMMachine& machine) {
  size_t n_gaussians = machine.getNGaussians();
  size_t n_inputs = machine.getNInputs();
  bp::ndarray varianceThresholds(ca::t_float64, n_gaussians, n_inputs);
  blitz::Array<double,2> varianceThresholds_ = varianceThresholds.bz<double,2>();
  machine.getVarianceThresholds(varianceThresholds_);
  return varianceThresholds.self();
}

static void py_gmmmachine_setVarianceThresholds(mach::GMMMachine& machine, bp::const_ndarray varianceThresholds) {
  const ca::typeinfo& info = varianceThresholds.type();
  if(info.dtype != ca::t_float64 || info.nd != 2)
    PYTHON_ERROR(TypeError, "cannot set array of type '%s'", info.str().c_str());
  machine.setVarianceThresholds(varianceThresholds.bz<double,2>());
}

static void py_gmmmachine_setVarianceThresholdsOther(mach::GMMMachine& machine, object o) {
  extract<int> int_check(o);
  extract<double> float_check(o);
  if(int_check.check()) { //is int
    machine.setVarianceThresholds(int_check());
  }
  else if(float_check.check()) { //is float
    machine.setVarianceThresholds(float_check());
  }
  else {
    //try hard-core extraction - throws TypeError, if not possible
    blitz::Array<double,1> val = extract<blitz::Array<double,1> >(o);
    machine.setVarianceThresholds(val);
  }
}

static double py_gmmmachine_loglikelihoodA(const mach::GMMMachine& machine, bp::const_ndarray x, bp::ndarray ll) {
  blitz::Array<double,1> ll_ = ll.bz<double,1>();
  return machine.logLikelihood(x.bz<double,1>(), ll_);
}

static double py_gmmmachine_loglikelihoodA_(const mach::GMMMachine& machine, bp::const_ndarray x, bp::ndarray ll) {
  blitz::Array<double,1> ll_ = ll.bz<double,1>();
  return machine.logLikelihood_(x.bz<double,1>(), ll_);
}

static double py_gmmmachine_loglikelihoodB(const mach::GMMMachine& machine, bp::const_ndarray x) {
  return machine.logLikelihood(x.bz<double,1>());
}

static double py_gmmmachine_loglikelihoodB_(const mach::GMMMachine& machine, bp::const_ndarray x) {
  return machine.logLikelihood_(x.bz<double,1>());
}

static void py_gmmmachine_accStatistics(const mach::GMMMachine& machine, bp::const_ndarray x, mach::GMMStats& gs) {
  machine.accStatistics(x.bz<double,1>(), gs);
}

static void py_gmmmachine_accStatistics_(const mach::GMMMachine& machine, bp::const_ndarray x, mach::GMMStats& gs) {
  machine.accStatistics_(x.bz<double,1>(), gs);
}

void bind_machine_gmm() 
{
  class_<mach::GMMStats, boost::shared_ptr<mach::GMMStats> >("GMMStats",
      "A container for GMM statistics.\n"
      "With respect to Reynolds, \"Speaker Verification Using Adapted "
      "Gaussian Mixture Models\", DSP, 2000:\n"
      "Eq (8) is n(i)\n"
      "Eq (9) is sumPx(i) / n(i)\n"
      "Eq (10) is sumPxx(i) / n(i)\n",
      init<>())
    .def(init<const size_t, const size_t>(args("n_gaussians","n_inputs")))
    .def(init<io::HDF5File&>(args("config")))
    .def(init<bob::machine::GMMStats&>(args("other"), "Creates a GMMStats from another GMMStats, using the copy constructor."))
    .def(self == self)
    .def(self != self)
    .def_readwrite("log_likelihood", &mach::GMMStats::log_likelihood, "The accumulated log likelihood of all samples")
    .def_readwrite("t", &mach::GMMStats::T, "The accumulated number of samples")
    .add_property("n", &py_gmmstats_getN, &py_gmmstats_setN, "For each Gaussian, the accumulated sum of responsibilities, i.e. the sum of P(gaussian_i|x)")
    .add_property("sum_px", &py_gmmstats_getSumpx, &py_gmmstats_setSumpx, "For each Gaussian, the accumulated sum of responsibility times the sample ")
    .add_property("sum_pxx", &py_gmmstats_getSumpxx, &py_gmmstats_setSumpxx, "For each Gaussian, the accumulated sum of responsibility times the sample squared")
    .def("resize", &mach::GMMStats::resize, args("n_gaussians", "n_inputs"),
         " Allocates space for the statistics and resets to zero.")
    .def("init", &mach::GMMStats::init, "Resets statistics to zero.")
    .def("save", &mach::GMMStats::save, "Save to a Configuration")
    .def("load", &mach::GMMStats::load, "Load from a Configuration")
    .def(self_ns::str(self_ns::self))
    .def(self_ns::self += self_ns::self)
  ;
  
  class_<mach::GMMMachine, boost::shared_ptr<mach::GMMMachine>, bases<mach::Machine<blitz::Array<double,1>, double> > >("GMMMachine",
      "This class implements a multivariate diagonal Gaussian distribution.\n"
      "See Section 2.3.9 of Bishop, \"Pattern recognition and machine learning\", 2006",
      init<>())
    .def(init<const size_t, const size_t>(args("n_gaussians", "n_inputs")))
    .def(init<bob::machine::GMMMachine&>(args("other"), "Creates a GMMMachine from another GMMMachine, using the copy constructor."))
    .def(init<io::HDF5File&>(args("config")))
    .def(self == self)
    .def(self != self)
    .add_property("dim_d", &mach::GMMMachine::getNInputs, &mach::GMMMachine::setNInputs, "The feature dimensionality D")
    .add_property("dim_c", &mach::GMMMachine::getNGaussians, "The number of Gaussian components C")
    .add_property("weights", &py_gmmmachine_getWeights, &py_gmmmachine_setWeights, "The weights (also known as \"mixing coefficients\")")
    .add_property("means", &py_gmmmachine_getMeans, &py_gmmmachine_setMeans, "The means of the gaussians")
    .add_property("mean_supervector", &py_gmmmachine_getMeanSupervector, &py_gmmmachine_setMeanSupervector,
                  "The mean supervector of the GMMMachine "
                  "(concatenation of the mean vectors of each Gaussian of the GMMMachine")
    .add_property("variances", &py_gmmmachine_getVariances, &py_gmmmachine_setVariances, "The (diagonal) variances of the Gaussians")
    .add_property("variance_supervector", &py_gmmmachine_getVarianceSupervector, &py_gmmmachine_setVarianceSupervector,
                  "The variance supervector of the GMMMachine "
                  "(concatenation of the variance vectors of each Gaussian of the GMMMachine")
    .add_property("variance_thresholds", &py_gmmmachine_getVarianceThresholds, &py_gmmmachine_setVarianceThresholds,
                  "The variance flooring thresholds for each Gaussian in each dimension")
    .def("resize", &mach::GMMMachine::resize, args("n_gaussians", "n_inputs"),
         "Reset the input dimensionality, and the number of Gaussian components.\n"
         "Initialises the weights to uniform distribution.")
    .def("set_variance_thresholds", &py_gmmmachine_setVarianceThresholdsOther, args("variance_threshold"),
         "Set the variance flooring thresholds in each dimension to the same vector for all Gaussian components if the argument is a 1D numpy arrray, and equal for all Gaussian components and dimensions if the parameter is a scalar.")
    .def("get_gaussian", &mach::GMMMachine::getGaussian, args("i"),
         "Get the specified Gaussian component. An exception is thrown if i is out of range.")

    .def("log_likelihood", &py_gmmmachine_loglikelihoodA, args("self", "x", "log_weighted_gaussian_likelihoods"),
         "Output the log likelihood of the sample, x, i.e. log(p(x|mach::GMMMachine)). Inputs are checked.")
    .def("log_likelihood_", &py_gmmmachine_loglikelihoodA_, args("self", "x", "log_weighted_gaussian_likelihoods"),
         "Output the log likelihood of the sample, x, i.e. log(p(x|mach::GMMMachine)). Inputs are NOT checked.")
    .def("log_likelihood", &py_gmmmachine_loglikelihoodB, args("self", "x"),
         " Output the log likelihood of the sample, x, i.e. log(p(x|GMM)). Inputs are checked.")
    .def("log_likelihood_", &py_gmmmachine_loglikelihoodB_, args("self", "x"),
         " Output the log likelihood of the sample, x, i.e. log(p(x|GMM)). Inputs are checked.")
    .def("acc_statistics", &py_gmmmachine_accStatistics, args("self", "x", "stats"),
         "Accumulate the GMM statistics for this sample. Inputs are checked.")
    .def("acc_statistics_", &py_gmmmachine_accStatistics_, args("self", "x", "stats"),
         "Accumulate the GMM statistics for this sample. Inputs are NOT checked.")
    .def("acc_statistics",
         (void (mach::GMMMachine::*)(const blitz::Array<double,2>&, mach::GMMStats&) const)&mach::GMMMachine::accStatistics,
         args("sampler", "stats"), "Accumulates the GMM statistics over a set of samples. Inputs are checked.")
    .def("acc_statistics_",
         (void (mach::GMMMachine::*)(const blitz::Array<double,2>&, mach::GMMStats&) const)&mach::GMMMachine::accStatistics_,
         args("sampler", "stats"), "Accumulates the GMM statistics over a set of samples. Inputs are NOT checked.")
    .def("load", &mach::GMMMachine::load, "Load from a Configuration")
    .def("save", &mach::GMMMachine::save, "Save to a Configuration")
    .def(self_ns::str(self_ns::self))
  ;

  class_<mach::GMMLLRMachine, bases<mach::Machine<blitz::Array<double,1>, double> > >("GMMLLRMachine",
       "This class implements computes log likelihood ratio, given a client and a UBM GMM.\n",
        no_init)
    .def(init<mach::GMMLLRMachine&>())
    .def(init<io::HDF5File&>(args("config")))
    .def(init<io::HDF5File&,io::HDF5File&>(args("client", "ubm")))
    .def(init<mach::GMMMachine&,mach::GMMMachine&>(args("client", "ubm")))
    .def(self == self)
    .def("get_gmm_client",
         &mach::GMMLLRMachine::getGMMClient, return_value_policy<reference_existing_object>(),
         "Get a pointer to the client GMM")
    .def("get_gmm_ubm",
         &mach::GMMLLRMachine::getGMMUBM, return_value_policy<reference_existing_object>(),
         "Get a pointer to the UBM GMM")
    .add_property("n_inputs", &mach::GMMMachine::getNInputs, "The feature dimensionality")
    .def("load", &mach::GMMLLRMachine::load, "Load from a Configuration")
    .def("save", &mach::GMMLLRMachine::save, "Save to a Configuration")
    .def(self_ns::str(self_ns::self))
  ;
}
