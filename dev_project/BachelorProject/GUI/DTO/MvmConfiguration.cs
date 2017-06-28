using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.DTO
{
    [Serializable]
    public class MvmConfiguration
    {
        public string Name { get; set; }
        public string FilePath { get; set; }
        public List<LedTriangle> LedTriangles { get; set; }

    }
}
