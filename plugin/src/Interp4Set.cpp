#include <iostream>
#include "Interp4Set.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _Name(""), _Wsp_x(0), _Wsp_y(0), _Wsp_z(0), _Angle_x(0), _Angle_y(0), _Angle_z(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name  << _Wsp_x << _Wsp_y << _Wsp_z << _Angle_x << _Angle_y << _Angle_z << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd(Scene* scene) const
{
    MobileObj* obj = scene->FindMobileObj(_Name.c_str());
    if (!obj)
    {
        std::cerr << "Error: Mobile object '" << _Name << "' not found in the scene." << std::endl;
        return false;
    }

    Vector3D new_pos;
    new_pos[0] = _Wsp_x;
    new_pos[1] = _Wsp_y;
    new_pos[2] = _Wsp_z;

    obj->SetPosition_m(new_pos);

    obj->SetAng_Roll_deg(_Angle_x);
    obj->SetAng_Pitch_deg(_Angle_y);
    obj->SetAng_Yaw_deg(_Angle_z);

    scene->LockAccess();
    scene->MarkChange();
    scene->UnlockAccess();

    usleep(10000);

    return true;
}



/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Name))
  {
      std::cout << "Error: Failed to read object name." << std::endl;
      return false;
  }

  if (!(Strm_CmdsList >> _Wsp_x >> _Wsp_y >> _Wsp_z))
  {
      std::cout << "Error: Failed to read coordinates (x, y, z)." << std::endl;
      return false;
  }

  if (!(Strm_CmdsList >> _Angle_x >> _Angle_y >> _Angle_z))
  {
      std::cout << "Error: Failed to read angles (OX, OY, OZ)." << std::endl;
      return false;
  }

  return true;
}



/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set nazwa_obiektu wsp_x wsp_y wsp_z kat_OX kat_OY kat_OZ" << endl;
}
