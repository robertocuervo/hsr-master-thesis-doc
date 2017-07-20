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
        public LedTriangle(string name, float x, float y, float z)
        {
            Name = name;
            Triangle = new Triangle(x,y,z);
        }
        public string Name { get; set; }
        public Triangle Triangle { get; set; }

        public override string ToString()
        {
            return $"{Name} ({Triangle.X}, {Triangle.Y}, {Triangle.Z})";
        }
    }
}
