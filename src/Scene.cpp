#include "Scene.hh"

Scene::Scene(Configuration& config)
{
  for (const auto& objectConfig : config._ObjectsConfig)
  {
    MobileObj tmp;
    tmp.SetName(objectConfig.name.c_str());
    tmp.SetAng_Roll_deg(objectConfig.rot[0]);
    tmp.SetAng_Pitch_deg(objectConfig.rot[1]);
    tmp.SetAng_Yaw_deg(objectConfig.rot[2]);
    tmp.SetPosition_m(objectConfig.shift);
    tmp.setRgb(objectConfig.rgb);
    tmp.setScale(objectConfig.scale);
    tmp.setTranslation(objectConfig.trans);

    AddMobileObj(&tmp);
    std::cout << "Added object: " << tmp.GetName() << std::endl;
  }
}



void Scene::AddMobileObj(MobileObj *pMobObj)
{
  _Container4Objects.insert(std::make_pair(pMobObj->GetName(), *pMobObj));
}
