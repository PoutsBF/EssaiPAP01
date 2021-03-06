/******************************************************************************
    Gestion des Boutons Poussoirs                   Stéphane Lepoutère (c) 2020

    Observe l'arrivée de changement d'état sur les BP (interruption)
    Gère le débounce
    Détecte les appuis courts, longs, doubles clics et l'état instantané
    2020-11-07 : à faire : modification de la philosophie du double clic :
        un double clic est considéré comme un clic qui arrive dans un délai 
        court après le précédent. Le premier clic est sensé avoir été pris 
        en compte.
*/

#pragma once
#ifndef GESTIONBP_H
#define GESTIONBP_H
#include <Arduino.h>

//-----------------------------------------------------------------------------
//---- Définition des constantes ----
const unsigned long BP_delai_appuie_court = 500;
const unsigned long BP_delai_appuie_long = 500;
const unsigned long BP_delai_double = 300;
const unsigned long BP_delai_rebond = 5;
enum BP_MESSAGES
{
    BP_MESS_IDLE,
    BP_MESS_APPUYE,
    BP_MESS_RELACHE,
    BP_MESS_APPUIE_COURT,
    BP_MESS_APPUIE_LONG,
    BP_MESS_APPUIE_DOUBLE
};

const uint8_t BP0_pin = 2;
const uint8_t BP1_pin = 4;

#define BP_PILE_TAILLE      16

//-----------------------------------------------------------------------------
//---- Définition des structures ----
struct BP_struct_msg
{
    uint8_t idBP;
    uint8_t idMsg;
};

struct BP_struct_pile
{
    uint8_t idBP;
    uint8_t etat;
    unsigned long time;
};
//-----------------------------------------------------------------------------
//---- Définition des structures ----

class GestionBP
{
    public:
//        GestionBP(void);
        void init(void);
        static void interruption(void);

        uint8_t handle(BP_struct_msg *msg);

    private:
        static void push(uint8_t idBP, uint8_t etat, unsigned long delta);
        uint8_t pop(uint8_t *idBP, uint8_t *etat, unsigned long *delta);

        static BP_struct_pile pile[BP_PILE_TAILLE];
        static uint8_t pile_pos_entree;
        static uint8_t pile_pos_sortie;
};

#endif