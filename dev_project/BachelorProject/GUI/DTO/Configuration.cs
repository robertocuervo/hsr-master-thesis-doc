using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI
{
    [Serializable]
    public class Configuration
    {
        //UserValues
        public float referenceSphere1X;
        public float referenceSphere1Y;
        public float referenceSphere1Z;
        public float referenceSphere2X;
        public float referenceSphere2Y;
        public float referenceSphere2Z;
        public float referenceSphere3X;
        public float referenceSphere3Y;
        public float referenceSphere3Z;

        public float calibrationVertex1X;
        public float calibrationVertex1Y;
        public float calibrationVertex1Z;
        public float calibrationVertex2X;
        public float calibrationVertex2Y;
        public float calibrationVertex2Z;
        public float calibrationVertex3X;
        public float calibrationVertex3Y;
        public float calibrationVertex3Z;

        public int frequency;

        public bool displayReferenceCube;

        public string mvmFilePath;
        public string mvmReferenceFilePath;
        public List<string> stlFilePaths;

        //Internal values
        public string windowName = "JawBone Visualizer";
        public string vertexPath = "../Viewer/loading.vert";
        public string fragmentPath = "../Viewer/loading.frag";
        public string uniformModel = "model";
        public string uniformViewPos = "viewPos";
        public string uniformProjection = "projection";
        public string uniformView = "view";
        public string uniformLightAmbient = "light.ambient";
        public string uniformLightDiffuse = "light.diffuse";
        public string uniformLightSpecular = "light.specular";
        public string uniformMaterialShininess = "material.shininess";
        public string uniformLightDirection = "light.direction";

        public float positivePitchBound = 89f;
        public float negativePitchBound = 0f;
        public float yaw = -90f;
        public float pitch = 0f;
        public float speed = 3f;
        public float sensitivity = 0.25f;
        public float zoom = 45f;

        public int screenWidth = 1920;
        public int sceenHeight = 1080;
    }
}
