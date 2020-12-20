namespace Xbim.Common.Geometry
{
    public interface IXbimGeometryParser
    {
        XbimCurveData Parse(IXbimCurve xbimCurve);

        XbimCurveData Parse(IXbimEdge xbimEdge);
    }
}
