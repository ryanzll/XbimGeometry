namespace Xbim.Common.Geometry
{
    public enum XbimCurveType
    {
        Undefined,
        Line,
        Circle,
        Ellipse
    }

    public class XbimCurveData
    {
        public virtual XbimCurveType CurveType { get { return XbimCurveType.Undefined; } }

        public double FirstParameter { get; set; }

        public double LastParameter { get; set; }
    }

    public class XbimLineData: XbimCurveData
    {
        public override XbimCurveType CurveType { get { return XbimCurveType.Line; } }
    }

    public class XbimCircleData: XbimCurveData
    {
        public XbimPoint3D Center { get; set; }

        public double Radius { get; set; }

        public XbimVector3D Normal { get; set; }

        public XbimVector3D XDirection { get; set; }

        public override XbimCurveType CurveType { get { return XbimCurveType.Circle; } }
    }
}
