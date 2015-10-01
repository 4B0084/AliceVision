#if HAVE_ALEMBIC

#pragma once


#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreHDF5/All.h>

#include <openMVG/sfm/sfm_data.hpp>

namespace openMVG {
namespace dataio {

class AlembicExporter
{
public:

  AlembicExporter(const std::string &filename)
  : archive(Alembic::AbcCoreHDF5::WriteArchive(), filename)
  , topObj(archive, Alembic::Abc::kTop)
  , counter(0)
  {
  }

  /**
   * @brief Add a set of 3D points from a SFM scene
   * @param points The 3D points to add
   */
  void addPoints(const sfm::Landmarks &points);

  /**
   * @brief Add a single camera
   * 
   * @param name An identifier for the camera
   * @param pose The camera pose
   * @param cam The camera intrinsics
   */
  void appendCamera(const std::string &name, 
                    const geometry::Pose3 &pose, 
                    const cameras::Pinhole_Intrinsic *cam);
  
  /**
   * @brief Add a set of cameras contained in a SFM scene
   * 
   * @param sfmdata The structure containing the camera info
   */
  void addCameras(const sfm::SfM_Data &sfmdata);

  virtual ~AlembicExporter();

private:
  Alembic::Abc::OArchive archive;
  Alembic::Abc::OObject topObj;
  unsigned int counter;
};

} // namespace data_io
} // namespace openMVG

#endif // HAVE_ALEMBIC
