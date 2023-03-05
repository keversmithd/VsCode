#ifndef COLUMB_LAW_H
#define COLUMB_LAW_H
#include <math.h>

struct Vec4
{
    float x;
    float y;
    float z;
    float w;
};

struct PointCharge
{
    float charge;
    Vec4 Position;
};

struct ElectricallyChargedParticle
{
    const double K = 8.988 * pow(10,9); //Newton-meter squared per Coulomb squared
    //Newtons, Force required to accelerate a mass of one kilogram at a rate of one meter per second squared
    //Meters square, is the unit of area, size of two-dimensional object or surface.
    //Columbs i sthe unit of electrical charge, it is defined as the cahrge carried by a constant current of one ampere flowing for one second.
    //It is used to express the force per unit charge at a point in space where an electric field is present.

    //magnitude of the electrostatic force, of attraction or repulsion between two point charges
    //directly proportional to the
    //product of the magnitudes of charges
    //and inversely proportional to the square of the distance between them.
    void ColumbsLaw(PointCharge Q1, PointCharge Q2){
        //Vector from Q1 to Q2
        Vec4 ConnectionVector = { Q2.Position.x - Q1.Position.x, Q2.Position.y - Q1.Position.y, Q2.Position.z - Q1.Position.z, Q2.Position.w - Q1.Position.w };
        double distance = sqrt(pow(ConnectionVector.x,2) + pow(ConnectionVector.y,2) + pow(ConnectionVector.z, 2) + pow (ConnectionVector.w, 2));
        if(distance == 0) {distance += 0.000001;}
        double ForcePerUnitCharge = K*(Q1.charge * Q2.charge)/distance;

        //Vector from Q2 to Q1
        Vec4 ReconnectionVector = { Q1.Position.x - Q2.Position.x, Q1.Position.y - Q2.Position.y, Q1.Position.z - Q2.Position.z, Q1.Position.w - Q2.Position.w};
        double redistance = sqrt(pow(ReconnectionVector.x, 2) + pow(ReconnectionVector.y, 2) + pow(ReconnectionVector.z, 2) + pow(ReconnectionVector.w, 2));
        if(redistance == 0) {distance += 0.000001; }
        Vec4 UnitConnectionVector = { ConnectionVector.x/distance, ConnectionVector.y/distance, ConnectionVector.z/distance, ConnectionVector.w/distance };
        Vec4 UnitReconnectionVector = {ReconnectionVector.x/redistance, ReconnectionVector.y/redistance, ReconnectionVector.z/redistance, ReconnectionVector.w/redistance};

        Vec4 DirectionForceQ1 = {UnitConnectionVector.x * ForcePerUnitCharge, UnitConnectionVector.y * ForcePerUnitCharge, UnitConnectionVector.z * ForcePerUnitCharge, UnitConnectionVector.w * ForcePerUnitCharge};
        Vec4 DirectionForceQ2 = {UnitReconnectionVector.x * ForcePerUnitCharge, UnitReconnectionVector.y * ForcePerUnitCharge, UnitReconnectionVector.z * ForcePerUnitCharge, UnitConnectionVector.w * ForcePerUnitCharge};
        if(Q1.charge >= 0 && Q2.charge >= 0 || Q1.charge < 0 && Q2.charge < 0)
        {
            DirectionForceQ1 = {-DirectionForceQ1.x, -DirectionForceQ1.y, -DirectionForceQ1.z, -DirectionForceQ1.w};
            DirectionForceQ2 = {-DirectionForceQ2.x, -DirectionForceQ2.y, -DirectionForceQ2.z, -DirectionForceQ2.w};
        }
        //inverse square law, meaning its inversely proprotional to distance between the two objects.

    }
    //this force is along the straight line connection the point charges,
    //if the charges have the same sign, the electrostatic force between them is repulsive, if they have different signs the force between them is attractive.
    float CoulombForce;
};

void VectorFormColumbLaw(PointCharge Q1, PointCharge Q2)
{
    const double Vacuumpermittivity = 8.85418781762039 * pow(10,-12); // F/m
    const double PI = 3.14159265359;
    double ChargeMagnitude = Q1.charge * Q2.charge;
    double FPVC = 4 * PI * Vacuumpermittivity;
    Vec4 VectorialDistance = { Q1.Position.x - Q2.Position.x, Q1.Position.y - Q2.Position.y, Q1.Position.z - Q2.Position.z, Q1.Position.w - Q2.Position.w};
    double VectorialDistanceMagnitude = sqrt(pow(VectorialDistance.x, 2) + pow(VectorialDistance.y, 2) + pow(VectorialDistance.z, 2) + pow(VectorialDistance.w, 2));
    
    Vec4 UnitVectorial = {VectorialDistance.x/VectorialDistanceMagnitude, VectorialDistance.y/VectorialDistanceMagnitude, VectorialDistance.z/VectorialDistanceMagnitude, VectorialDistance.w/VectorialDistanceMagnitude};
    Vec4 CubeUnitVectorial = { UnitVectorial.x / pow(VectorialDistanceMagnitude, 2), UnitVectorial.y / pow(VectorialDistanceMagnitude,2), UnitVectorial.z / pow(VectorialDistanceMagnitude,2) , UnitVectorial.w / pow(VectorialDistanceMagnitude, 2) };

    Vec4 F1 = {FPVC * CubeUnitVectorial.x,  FPVC * CubeUnitVectorial.y, FPVC * CubeUnitVectorial.z, FPVC * CubeUnitVectorial.w };
}

#endif