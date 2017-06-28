using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.DTO
{
    [Serializable]
    public class LedTriangle
    {
        public string Name { get; set; }
        public Triangle Triangle { get; set; }
    }
}
