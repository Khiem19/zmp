#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include <string>
#include "Vector3D.hh"
#include "AbstractMobileObj.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy MobileObj
 *
 * Plik zawiera definicję klasy MobileObj.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */

/*!
 * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
 * Nazwy metod są obowiązujące.
 */
class MobileObj: public AbstractMobileObj
{
        /*!
         * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
         *        wokół osi \e OZ.
         *
         * Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
         * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
         */
        double _Ang_Yaw_deg = 0;

        /*!
         * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
         *        wokół osi \e OY.
         *
         * Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
         * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
         */
        double _Ang_Pitch_deg = 0;

        /*!
         * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
         *        wokół osi \e OX.
         *
         * Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
         * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
         */
        double _Ang_Roll_deg = 0;

        /*!
         * \brief Współrzędne aktualnej pozycji obiektu.
         *
         * Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
         * że współrzędne wyrażone są w metrach.
         */
        Vector3D _Position_m; // shift?

        /*!
         * \brief Nazwa obiektu, która go indentyfikuje.
         *
         * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
         * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
         */
        std::string _Name;
        Vector3D scale;
        Vector3D translation;
        Vector3D rgb;

public:
        /*!
         * \brief Udostępia wartość kąta \e roll.
         *
         * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
         */
        double GetAng_Roll_deg() const override {return _Ang_Roll_deg; }
        /*!
         * \brief Udostępia wartość kąta \e pitch.
         *
         * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
         */
        double GetAng_Pitch_deg() const override { return _Ang_Pitch_deg; }
        /*!
         * \brief Udostępia wartość kąta \e yaw.
         *
         * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
         */
        double GetAng_Yaw_deg() const override { return _Ang_Yaw_deg; }

        /*!
         * \brief Zmienia wartość kąta \e roll.
         *
         * Zmienia wartość kąta \e roll.
         * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
         */
        void SetAng_Roll_deg(double Ang_Roll_deg) override { _Ang_Roll_deg = Ang_Roll_deg; }
        /*!
         * \brief Zmienia wartość kąta \e pitch.
         *
         * Zmienia wartość kąta \e pitch.
         * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
         */
        void SetAng_Pitch_deg(double Ang_Pitch_deg) override { _Ang_Pitch_deg = Ang_Pitch_deg; }
        /*!
         * \brief Zmienia wartość kąta \e yaw.
         *
         * Zmienia wartość kąta \e yaw.
         * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
         */
        void SetAng_Yaw_deg(double Ang_Yaw_deg) override { _Ang_Yaw_deg = Ang_Yaw_deg; }

        /*!
         * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
         *
         * Udostępnia współrzędne punktu, który definiuje położenia obiektu
         * w trybie tylko do odczytu.
         * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
         */
        const Vector3D &GetPosition_m() const override { return _Position_m; }
        /*!
         * \brief Zmienia współrzędne położenia obiektu.
         *
         * Zmienia współrzędne punktu, który definiuje położenia obiektu.
         * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
         * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
         *                     że są one wyrażone w metrach.
         */
        void SetPosition_m(const Vector3D &rPos_m) override { _Position_m = rPos_m; }

        /*!
         * \brief Zmienia nazwę obiektu.
         *
         *  Zmienia nazwę obiektu.
         *  \param[in] sName - nowa nazwa obiektu.
         */
        void SetName(const char *sName) override { _Name = sName; }
        /*!
         * \brief Udostępnia nazwę obiektu.
         *
         * Udostępnia nazwę obiektu w trybie tylko do odczytu.
         */
        const std::string &GetName() const override { return _Name; }

        void setScale(Vector3D new_scale) { scale = new_scale; }
        void setRgb(Vector3D new_rgb) { rgb = new_rgb; }
        void setTranslation(Vector3D new_trans) { translation = new_trans; }
        std::string getUpdateInstruction() const;
        std::string getAddInstruction() const;
        Vector3D getScale() { return scale; }
        Vector3D getRgb() { return rgb; }
        Vector3D getTranslation() { return translation; }
};

#endif
