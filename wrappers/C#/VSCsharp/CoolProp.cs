/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class CoolProp {
  public static void UseSaturationLUT(bool OnOff) {
    CoolPropPINVOKE.UseSaturationLUT(OnOff);
  }

  public static bool SaturationLUTStatus() {
    bool ret = CoolPropPINVOKE.SaturationLUTStatus();
    return ret;
  }

  public static void UseSinglePhaseLUT(bool OnOff) {
    CoolPropPINVOKE.UseSinglePhaseLUT(OnOff);
  }

  public static bool SinglePhaseLUTStatus() {
    bool ret = CoolPropPINVOKE.SinglePhaseLUTStatus();
    return ret;
  }

  public static double IProps(int iOutput, int iName1, double Prop1, int iName2, double Prop2, int iFluid) {
    double ret = CoolPropPINVOKE.IProps(iOutput, iName1, Prop1, iName2, Prop2, iFluid);
    return ret;
  }

  public static int IsFluidType(string Ref, string Type) {
    int ret = CoolPropPINVOKE.IsFluidType(Ref, Type);
    return ret;
  }

  public static double DerivTerms(string Term, double T, double rho, string Ref) {
    double ret = CoolPropPINVOKE.DerivTerms__SWIG_0(Term, T, rho, Ref);
    return ret;
  }

  public static void Phase(string Fluid, double T, double p, string Phase_str) {
    CoolPropPINVOKE.Phase__SWIG_0(Fluid, T, p, Phase_str);
  }

  public static int Phase_Trho(string Fluid, double T, double p, string Phase_str) {
    int ret = CoolPropPINVOKE.Phase_Trho__SWIG_0(Fluid, T, p, Phase_str);
    return ret;
  }

  public static int Phase_Tp(string Fluid, double T, double rho, string Phase_str) {
    int ret = CoolPropPINVOKE.Phase_Tp__SWIG_0(Fluid, T, rho, Phase_str);
    return ret;
  }

  public static double F2K(double T_F) {
    double ret = CoolPropPINVOKE.F2K(T_F);
    return ret;
  }

  public static double K2F(double T) {
    double ret = CoolPropPINVOKE.K2F(T);
    return ret;
  }

  public static void PrintSaturationTable(string FileName, string Ref, double Tmin, double Tmax) {
    CoolPropPINVOKE.PrintSaturationTable(FileName, Ref, Tmin, Tmax);
  }

  public static void FluidsList(string arg0) {
    CoolPropPINVOKE.FluidsList__SWIG_0(arg0);
  }

  public static void get_aliases(string Ref, string aliases) {
    CoolPropPINVOKE.get_aliases__SWIG_0(Ref, aliases);
  }

  public static void get_REFPROPname(string Ref, string arg1) {
    CoolPropPINVOKE.get_REFPROPname__SWIG_0(Ref, arg1);
  }

  public static void get_errstring(string arg0) {
    CoolPropPINVOKE.get_errstring__SWIG_0(arg0);
  }

  public static string get_errstringc() {
    string ret = CoolPropPINVOKE.get_errstringc();
    return ret;
  }

  public static int get_errstring_copy(string arg0) {
    int ret = CoolPropPINVOKE.get_errstring_copy(arg0);
    return ret;
  }

  public static int get_svnrevision() {
    int ret = CoolPropPINVOKE.get_svnrevision();
    return ret;
  }

  public static int get_version(string pversion) {
    int ret = CoolPropPINVOKE.get_version__SWIG_0(pversion);
    return ret;
  }

  public static void get_index_units(int param, string units) {
    CoolPropPINVOKE.get_index_units__SWIG_0(param, units);
  }

  public static void get_1phase_LUT_params(SWIGTYPE_p_int nT, SWIGTYPE_p_int np, SWIGTYPE_p_double Tmin, SWIGTYPE_p_double Tmax, SWIGTYPE_p_double pmin, SWIGTYPE_p_double pmax) {
    CoolPropPINVOKE.get_1phase_LUT_params(SWIGTYPE_p_int.getCPtr(nT), SWIGTYPE_p_int.getCPtr(np), SWIGTYPE_p_double.getCPtr(Tmin), SWIGTYPE_p_double.getCPtr(Tmax), SWIGTYPE_p_double.getCPtr(pmin), SWIGTYPE_p_double.getCPtr(pmax));
  }

  public static int get_debug() {
    int ret = CoolPropPINVOKE.get_debug();
    return ret;
  }

  public static void debug(int level) {
    CoolPropPINVOKE.debug__SWIG_0(level);
  }

  public static double rhosatL_anc(string Fluid, double T) {
    double ret = CoolPropPINVOKE.rhosatL_anc(Fluid, T);
    return ret;
  }

  public static double rhosatV_anc(string Fluid, double T) {
    double ret = CoolPropPINVOKE.rhosatV_anc(Fluid, T);
    return ret;
  }

  public static double psatL_anc(string Fluid, double T) {
    double ret = CoolPropPINVOKE.psatL_anc(Fluid, T);
    return ret;
  }

  public static double psatV_anc(string Fluid, double T) {
    double ret = CoolPropPINVOKE.psatV_anc(Fluid, T);
    return ret;
  }

  public static double Props(string Fluid, string Output) {
    double ret = CoolPropPINVOKE.Props__SWIG_0(Fluid, Output);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static double Props1(string Fluid, string Output) {
    double ret = CoolPropPINVOKE.Props1(Fluid, Output);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static double Props(char Output, char Name1, double Prop1, char Name2, double Prop2, string Ref) {
    double ret = CoolPropPINVOKE.Props__SWIG_1(Output, Name1, Prop1, Name2, Prop2, Ref);
    return ret;
  }

  public static double Props(string Output, char Name1, double Prop1, char Name2, double Prop2, string Ref) {
    double ret = CoolPropPINVOKE.Props__SWIG_2(Output, Name1, Prop1, Name2, Prop2, Ref);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static double DerivTerms(string Term, double T, double rho, SWIGTYPE_p_Fluid pFluid) {
    double ret = CoolPropPINVOKE.DerivTerms__SWIG_1(Term, T, rho, SWIGTYPE_p_Fluid.getCPtr(pFluid));
    return ret;
  }

  public static double DerivTerms(string Term, double T, double rho, SWIGTYPE_p_Fluid pFluid, bool SinglePhase, bool TwoPhase) {
    double ret = CoolPropPINVOKE.DerivTerms__SWIG_2(Term, T, rho, SWIGTYPE_p_Fluid.getCPtr(pFluid), SinglePhase, TwoPhase);
    return ret;
  }

  public static int set_1phase_LUT_params(string Ref, int nT, int np, double Tmin, double Tmax, double pmin, double pmax, bool rebuild) {
    int ret = CoolPropPINVOKE.set_1phase_LUT_params__SWIG_0(Ref, nT, np, Tmin, Tmax, pmin, pmax, rebuild);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static int set_1phase_LUT_params(string Ref, int nT, int np, double Tmin, double Tmax, double pmin, double pmax) {
    int ret = CoolPropPINVOKE.set_1phase_LUT_params__SWIG_1(Ref, nT, np, Tmin, Tmax, pmin, pmax);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static int debug() {
    int ret = CoolPropPINVOKE.debug__SWIG_1();
    return ret;
  }

  public static void set_debug(int level) {
    CoolPropPINVOKE.set_debug(level);
  }

  public static void set_phase(string Phase_str) {
    CoolPropPINVOKE.set_phase(Phase_str);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
  }

  public static string Phase(string Fluid, double T, double p) {
    string ret = CoolPropPINVOKE.Phase__SWIG_1(Fluid, T, p);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string Phase_Trho(string Fluid, double T, double rho) {
    string ret = CoolPropPINVOKE.Phase_Trho__SWIG_1(Fluid, T, rho);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string Phase_Tp(string Fluid, double T, double p) {
    string ret = CoolPropPINVOKE.Phase_Tp__SWIG_1(Fluid, T, p);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string get_EOSReference(string Ref) {
    string ret = CoolPropPINVOKE.get_EOSReference(Ref);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string get_TransportReference(string Ref) {
    string ret = CoolPropPINVOKE.get_TransportReference(Ref);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string FluidsList() {
    string ret = CoolPropPINVOKE.FluidsList__SWIG_1();
    return ret;
  }

  public static string get_aliases(string Ref) {
    string ret = CoolPropPINVOKE.get_aliases__SWIG_1(Ref);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string get_REFPROPname(string Ref) {
    string ret = CoolPropPINVOKE.get_REFPROPname__SWIG_1(Ref);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string get_errstring() {
    string ret = CoolPropPINVOKE.get_errstring__SWIG_1();
    return ret;
  }

  public static string get_version() {
    string ret = CoolPropPINVOKE.get_version__SWIG_1();
    return ret;
  }

  public static int get_param_index(string param) {
    int ret = CoolPropPINVOKE.get_param_index(param);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static int get_Fluid_index(string param) {
    int ret = CoolPropPINVOKE.get_Fluid_index(param);
    if (CoolPropPINVOKE.SWIGPendingException.Pending) throw CoolPropPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string get_index_units(int index) {
    string ret = CoolPropPINVOKE.get_index_units__SWIG_1(index);
    return ret;
  }

  public static SWIGTYPE_p_Fluid get_fluid(int iFluid) {
    IntPtr cPtr = CoolPropPINVOKE.get_fluid(iFluid);
    SWIGTYPE_p_Fluid ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_Fluid(cPtr, false);
    return ret;
  }

}
