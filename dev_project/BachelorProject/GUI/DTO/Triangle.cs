using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI.DTO
{
    [Serializable]
    public class Triangle
    {
        public Triangle(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }
    }
}
