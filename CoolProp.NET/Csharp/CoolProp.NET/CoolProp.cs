/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class CoolProp {
  public static void Help() {
    CoolPropPINVOKE.Help();
  }

  public static void UseSaturationLUT(int OnOff) {
    CoolPropPINVOKE.UseSaturationLUT(OnOff);
  }

  public static void UseSinglePhaseLUT(int OnOff) {
    CoolPropPINVOKE.UseSinglePhaseLUT(OnOff);
  }

  public static int SinglePhaseLUTStatus() {
    int ret = CoolPropPINVOKE.SinglePhaseLUTStatus();
    return ret;
  }

  public static double Props(char Output, char Name1, double Prop1, char Name2, double Prop2, string Ref) {
    double ret = CoolPropPINVOKE.Props__SWIG_0(Output, Name1, Prop1, Name2, Prop2, Ref);
    return ret;
  }

  public static double Props(string Output, char Name1, double Prop1, char Name2, double Prop2, string Ref) {
    double ret = CoolPropPINVOKE.Props__SWIG_1(Output, Name1, Prop1, Name2, Prop2, Ref);
    return ret;
  }

  public static void PropsV(string Output, char Name1, SWIGTYPE_p_double Prop1, int len1, char Name2, SWIGTYPE_p_double Prop2, int len2, string Ref, SWIGTYPE_p_double OutVec, int n) {
    CoolPropPINVOKE.PropsV(Output, Name1, SWIGTYPE_p_double.getCPtr(Prop1), len1, Name2, SWIGTYPE_p_double.getCPtr(Prop2), len2, Ref, SWIGTYPE_p_double.getCPtr(OutVec), n);
  }

  public static double Props(string Fluid, string Output) {
    double ret = CoolPropPINVOKE.Props__SWIG_2(Fluid, Output);
    return ret;
  }

  public static double pcrit(string Ref) {
    double ret = CoolPropPINVOKE.pcrit(Ref);
    return ret;
  }

  public static double Tcrit(string Ref) {
    double ret = CoolPropPINVOKE.Tcrit(Ref);
    return ret;
  }

  public static double Ttriple(string Ref) {
    double ret = CoolPropPINVOKE.Ttriple(Ref);
    return ret;
  }

  public static int IsFluidType(string Ref, string Type) {
    int ret = CoolPropPINVOKE.IsFluidType(Ref, Type);
    return ret;
  }

  public static double T_hp(string Ref, double h, double p, double T_guess) {
    double ret = CoolPropPINVOKE.T_hp(Ref, h, p, T_guess);
    return ret;
  }

  public static double h_sp(string Ref, double s, double p, double T_guess) {
    double ret = CoolPropPINVOKE.h_sp(Ref, s, p, T_guess);
    return ret;
  }

  public static double Tsat(string Ref, double p, double Q, double T_guess) {
    double ret = CoolPropPINVOKE.Tsat(Ref, p, Q, T_guess);
    return ret;
  }

  public static double DerivTerms(string Term, double T, double rho, string Ref) {
    double ret = CoolPropPINVOKE.DerivTerms(Term, T, rho, Ref);
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

  public static int Phase(double T, double rho, string Ref) {
    int ret = CoolPropPINVOKE.Phase(T, rho, Ref);
    return ret;
  }

  public static readonly int PHASE_SUPERCRITICAL = CoolPropPINVOKE.PHASE_SUPERCRITICAL_get();
  public static readonly int PHASE_SUPERHEATED = CoolPropPINVOKE.PHASE_SUPERHEATED_get();
  public static readonly int PHASE_SUBCOOLED = CoolPropPINVOKE.PHASE_SUBCOOLED_get();
  public static readonly int PHASE_TWOPHASE = CoolPropPINVOKE.PHASE_TWOPHASE_get();
  public static readonly int FLUIDTYPE_REFPROP = CoolPropPINVOKE.FLUIDTYPE_REFPROP_get();
  public static readonly int FLUIDTYPE_BRINE = CoolPropPINVOKE.FLUIDTYPE_BRINE_get();
  public static readonly int FLUIDTYPE_REFRIGERANT_PURE = CoolPropPINVOKE.FLUIDTYPE_REFRIGERANT_PURE_get();
  public static readonly int FLUIDTYPE_REFRIGERANT_PSEUDOPURE = CoolPropPINVOKE.FLUIDTYPE_REFRIGERANT_PSEUDOPURE_get();
}
