#include <iostream>
#include "Interp4Move.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Name(""), _Speed_mmS(0), _Distance_mm(0)
{}



/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name  << _Speed_mmS << _Distance_mm << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd(Scene* scene) const
{
    MobileObj* obj = scene->FindMobileObj(_Name.c_str());
    if (!obj)
    {
      std::cerr << "Error: Mobile object '" << _Name << "' not found in the scene." << std::endl;
      return false;
    }

    const double roll = obj->GetAng_Roll_deg();
    const double pitch = obj->GetAng_Pitch_deg();
    const double yaw = obj->GetAng_Yaw_deg();
    const Vector3D position = obj->GetPosition_m();

    const double time = _Distance_mm / _Speed_mmS;
    const double steps = static_cast<int>(time * N);
    const double step_distance = _Distance_mm / steps;

    scene->LockAccess();

    Vector3D move = position;
    for (int i = 0; i < steps; ++i)
    {
      const double delta_x = step_distance * cos(pitch * M_PI / 180) * cos(yaw * M_PI / 180);
      const double delta_y = step_distance * (cos(roll * M_PI / 180) * sin(yaw * M_PI / 180) +
                                              cos(yaw * M_PI / 180) * sin(pitch * M_PI / 180) * sin(roll * M_PI / 180));
      const double delta_z = step_distance * (sin(roll * M_PI / 180) * sin(yaw * M_PI / 180) -
                                              cos(roll * M_PI / 180) * cos(yaw * M_PI / 180) * sin(pitch * M_PI / 180));

      move[0] += delta_x;
      move[1] += delta_y;
      move[2] += delta_z;

      obj->SetPosition_m(move);
      scene->MarkChange();

      usleep(5000);
    }

    scene->UnlockAccess();

    return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Speed_mmS))
  {
    std::cout << "Blad wczytywania predkosci obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Distance_mm))
  {
    std::cout << "Blad wczytywania odleglosci" << std::endl;
    return 1;
  }
  return 0;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  nazwa_obiektu  szybkosc[mm/s]  dlugosc_drogi[mm]" << endl;
}
