#include <iostream>
#include "Interp4Rotate.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Name(""), _Axis(""), _Ang_speed(0), _Angle(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name  << _Axis << _Ang_speed << _Angle << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd(Scene* scene) const
{
    MobileObj* obj = scene->FindMobileObj(_Name.c_str());
    if (!obj)
    {
      std::cerr << "Error: Mobile object '" << _Name << "' not found in the scene." << std::endl;
      return false;
    }

    double roll = obj->GetAng_Roll_deg();
    double pitch = obj->GetAng_Pitch_deg();
    double yaw = obj->GetAng_Yaw_deg();

    double time = _Angle / _Ang_speed;
    double steps = static_cast<int>(time * N);
    double step_distance = _Angle / steps;
    double step = 100;

    double rotation = 0;

    int axis_idx = 0;
    switch (_Axis[0])
    {
    case 'O':
      axis_idx = (_Axis[1] == 'X') ? 1 : ((_Axis[1] == 'Y') ? 2 : ((_Axis[1] == 'Z') ? 3 : 0));
      break;
    default:
      std::cout << "Błędna nazwa osi obrotu: " << _Axis << std::endl;
      return false;
    }

    for (int i = 0; i < steps; ++i)
    {
      scene->LockAccess();

      rotation += step_distance;
      switch (axis_idx)
      {
      case 1:
          obj->SetAng_Roll_deg(roll + rotation);
          break;
      case 2:
          obj->SetAng_Pitch_deg(pitch + rotation);
          break;
      case 3:
          obj->SetAng_Yaw_deg(yaw + rotation);
          break;
      }

      scene->MarkChange();
      scene->UnlockAccess();
      usleep(step);
    }

    return true;
}



/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  if (!(Strm_CmdsList >> _Name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Axis))
  {
    std::cout << "Blad wczytywania nazwy osi" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Ang_speed))
  {
    std::cout << "Blad wczytywania predkosci katowej obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Angle))
  {
    std::cout << "Blad wczytywania kata" << std::endl;
    return 1;
  }
  return 0;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate nazwa_obiektu nazwa_osi szybkość_kątowa kąt_obrotu" << endl;
}
