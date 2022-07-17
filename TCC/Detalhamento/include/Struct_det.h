#ifndef STRUCT_DET_H
#define STRUCT_DET_H

struct malha
{
    int    N          ; //     Númerto de pontos na malha
    double n          ; // (m) Espaçamento entre pontos da malha
    int    numRegioes ; //     Número de regiões no diagrama de momento fletor 
    int   *raizes     ; //     Raizes no diagrama de momento fletor           [numRaizes]
};

struct solicitações
{
    double  Md_min ; // (kNm) Momento mínimo
    double *Vd     ; // (kN)  Vd diagrama       [N]
    double *Md_dec ; // (kNm) Momento decalado  [N]
};

struct geometria
{
    double altura      ; // (m) altura da viga
    double largura     ; // (m) largura da viga
    double comprimento ; // (m) comprimento da viga
    double cob         ; // (m) cobrimento da armadura
    double d           ; // (m) altura útil da viga
    double d2          ; // (m) distância face - armadura superior
};

struct propriedades
{
    double Ec       ; // (GPa) Módulo de elasticidade do concreto
    double Es       ; // (GPa) Módulo de elasticidade do aço
    double Ic       ; // (m^4) Momento de inércia da seção de concreto
    double fck      ; // (MPa) Resistência a compressão do concreto
    double fctd     ; // (MPa) Resistência a tração do concreto
    double fct_m    ; // (MPa) Resistência a tração média do concreto
    double fctk_inf ; // (MPa) Resistência a tração inferior do concreto
    double fctk_sup ; // (MPa) Resistência a tração superior do concreto
    double fyd      ; // (MPa) Resistência a tração/compressão das barras longitudinais
    double fywd     ; // (MPa) Resistência a tração/compressão das barras transversais

    int classeAgressividade ; // Classe de agressividade do meio
};

struct armaduras
{
    double *A_neg    ; // (  m²   )   Armadura longitudinal de tração em cada seção             [N]
    double *A_const  ; // (  m²   )   Armadura longitudinal construtiva em cada seção           [N]
    double *A_comp   ; // (  m²   )   Armadura longitudinal positiva complementar em cada seção [N]
    double *Asw      ; // (  m²/m )   Armadura transversal em cada seção                        [N]
    double  A_pele   ; // (  m²   )   Armadura longitudinal de pele para cada face
    double  Al_min   ; // (  m²   )   Armadura longitudinal mínima
    double  Asw_min  ; // (  m²   )   Armadura longitudinal positiva complementar

};

struct barras
{
    int   *N_neg    ; //     Número de barras para armadura negativo      [N]
    int   *N_const  ; //     Número de barras para armadura construtiva   [N]
    int   *N_comp   ; //     Número de barras para armadura complementar  [N]
    int   *N_Lmin   ; //     Número de barras para armadura mínima        [N]
    float *Bt_neg   ; // (mm) Bitola das barras para armadura negativo    [N]
    float *Bt_pos   ; // (mm) Bitola das barras para armadura mínima      [N]
    float *Bt_const ; // (mm) Bitola das barras para armadura construtiva [N]

};

struct viga
{
    int numero; // número da viga

    struct solicitações solicit ;
    struct geometria    geo     ;
    struct propriedades prop    ;
    struct armaduras    arm     ;
    struct malha        malha   ;
    struct barras       barras  ;
};

#endif