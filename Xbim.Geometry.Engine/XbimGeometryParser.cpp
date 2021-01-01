#include "XbimGeometryParser.h"
#include "XbimSolid.h"
#include "XbimCurve.h"
#include "XbimEdge.h"
#include <Geom_Curve.hxx>
#include <BRepTools.hxx>
#include <gp_Circ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Ax1.hxx>
#include <gp_Dir.hxx>
#include <Standard_Handle.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <Geom_Ellipse.hxx>

//using namespace opencascade;

namespace Xbim
{
	namespace Geometry
	{
		/*XbimLine::XbimLine(const Handle(Geom_Line)& line):XbimCurve(line)
		{
			pLine = new Handle(Geom_Line);
			*pLine = line;
		}

		XbimCircle::XbimCircle(const Handle(Geom_Circle)& circle) :XbimCurve(circle)
		{
			pCircle = new Handle(Geom_Circle);
			*pCircle = circle;
		}

		XbimPoint3D XbimCircle::Center::get()
		{
			gp_Circ gpCirc = (*pCircle)->Circ();
			const gp_Pnt gpPnt = gpCirc.Location();
			XbimPoint3D center = XbimPoint3D(gpPnt.X(), gpPnt.Y(), gpPnt.Z());
			return center;
		}

		XbimVector3D XbimCircle::Normal::get()
		{
			gp_Circ gpCirc = (*pCircle)->Circ();
			gp_Ax1 zAxis = gpCirc.Axis();
			gp_Dir zDir = zAxis.Direction();
			XbimVector3D normal = XbimVector3D(zDir.X(), zDir.Y(), zDir.Z());
			return normal;
		}

		XbimVector3D XbimCircle::XDirection::get()
		{
			gp_Circ gpCirc = (*pCircle)->Circ();
			gp_Ax1 xAxis = gpCirc.XAxis();
			gp_Dir xDir = xAxis.Direction();
			XbimVector3D xDirection = XbimVector3D(xDir.X(), xDir.Y(), xDir.Z());
			return xDirection;
		}

		XbimEllipse::XbimEllipse(const Handle(Geom_Ellipse)& ellipse) :XbimCurve(ellipse)
		{
			pEllipse = new Handle(Geom_Ellipse);
			*pEllipse = ellipse;
		}*/

		XbimCurveData^ XbimGeometryParser::Parse(IXbimCurve^ xbimCurve)
		{
			XbimCurve^ xbimCurveImpl = dynamic_cast<XbimCurve^>(xbimCurve);
			Handle(Geom_Curve) curve;
			curve = opencascade::handle<Geom_Curve>(xbimCurveImpl);
			if (curve->DynamicType() == STANDARD_TYPE(Geom_Line))
			{
			}
			if (curve->DynamicType() == STANDARD_TYPE(Geom_Circle))
			{
				return ParseCircle(opencascade::handle<Geom_Circle>::DownCast(curve));
			}
			return nullptr;
		}

		XbimCurveData^ XbimGeometryParser::ParseCircle(Handle_Geom_Circle circle)
		{
			gp_Circ gpCirc = circle->Circ();
			const gp_Pnt gpPnt = gpCirc.Location();
			XbimPoint3D center = XbimPoint3D(gpPnt.X(), gpPnt.Y(), gpPnt.Z());

			gp_Ax1 zAxis = gpCirc.Axis();
			gp_Dir zDir = zAxis.Direction();
			XbimVector3D normal = XbimVector3D(zDir.X(), zDir.Y(), zDir.Z());

			gp_Ax1 xAxis = gpCirc.XAxis();
			gp_Dir xDir = xAxis.Direction();
			XbimVector3D xDirection = XbimVector3D(xDir.X(), xDir.Y(), xDir.Z());

			XbimCircleData^ circleData = gcnew XbimCircleData();
			circleData->Center = center;
			circleData->Radius = circle->Radius();
			circleData->Normal = normal;
			circleData->XDirection = xDirection;

			return circleData;
		}

		XbimCurveData^ XbimGeometryParser::ParseLine(Handle_Geom_Line line)
		{
			XbimLineData^ lineData = gcnew XbimLineData();
			return lineData;
		}

		XbimCurveData^ XbimGeometryParser::Parse(IXbimEdge^ xbimEdge)
		{
			XbimEdge^ xbimEdgeImpl = dynamic_cast<XbimEdge^>(xbimEdge);
			//TopoDS_Edge topoDS_Edge = TopoDS_Edge(xbimEdgeImpl);
			const TopoDS_Edge topoDS_Edge = (const TopoDS_Edge &) (xbimEdgeImpl);
			TopLoc_Location loc;
			Standard_Real ff, ll;
			const Handle(Geom_Curve) curve = BRep_Tool::Curve(topoDS_Edge, loc, ff, ll);
			XbimCurveData^ curveData = nullptr;
			if (curve->DynamicType() == STANDARD_TYPE(Geom_Line))
			{
				curveData = ParseLine(opencascade::handle<Geom_Line>::DownCast(curve));
			}
			if (curve->DynamicType() == STANDARD_TYPE(Geom_Circle))
			{
				curveData = ParseCircle(opencascade::handle<Geom_Circle>::DownCast(curve));
			}

			if (nullptr != curveData)
			{
				curveData->FirstParameter = ff;
				curveData->LastParameter = ll;
			}

			return curveData;
		}

		void XbimGeometryParser::Parse(IXbimSolid^ xbimSolid)
		{
			XbimSolid^ xbimSolidImpl = dynamic_cast<XbimSolid^>(xbimSolid);
			String^ bRep = xbimSolid->ToBRep;
			//TopoDS_Edge topoDS_Edge = TopoDS_Edge(xbimEdgeImpl);
			const TopoDS_Solid topoDS_Solid = (const TopoDS_Solid&)(xbimSolidImpl);
		}
	}
}
