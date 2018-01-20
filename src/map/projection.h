#ifndef PROJECTION_H
#define PROJECTION_H

#include <QPointF>
#include <QDebug>
#include "common/coordinates.h"

class Datum;

class Projection {
public:
	class Setup {
	public:
		Setup() : _latitudeOrigin(NAN), _longitudeOrigin(NAN), _scale(NAN),
		  _falseEasting(NAN), _falseNorthing(NAN), _standardParallel1(NAN),
		  _standardParallel2(NAN) {}
		Setup(double latitudeOrigin, double longitudeOrigin, double scale,
		  double falseEasting, double falseNorthing, double standardParallel1,
		  double standardParallel2) : _latitudeOrigin(latitudeOrigin),
		  _longitudeOrigin(longitudeOrigin), _scale(scale),
		  _falseEasting(falseEasting), _falseNorthing(falseNorthing),
		  _standardParallel1(standardParallel1),
		  _standardParallel2(standardParallel2) {}

		double latitudeOrigin() const {return _latitudeOrigin;}
		double longitudeOrigin() const {return _longitudeOrigin;}
		double scale() const {return _scale;}
		double falseEasting() const {return _falseEasting;}
		double falseNorthing() const {return _falseNorthing;}
		double standardParallel1() const {return _standardParallel1;}
		double standardParallel2() const {return _standardParallel2;}

		void setLatitudeOrigin(double val) {_latitudeOrigin = val;}
		void setLongitudeOrigin(double val) {_longitudeOrigin = val;}
		void setScale(double val) {_scale = val;}
		void setFalseEasting(double val) {_falseEasting = val;}
		void setFalseNorthing(double val) {_falseNorthing = val;}
		void setStandardParallel1(double val) {_standardParallel1 = val;}
		void setStandardParallel2(double val) {_standardParallel2 = val;}

		bool isNull() const {return std::isnan(_latitudeOrigin)
		  && std::isnan(_longitudeOrigin) && std::isnan(_scale)
		  && std::isnan(_falseEasting) && std::isnan(_falseNorthing)
		  && std::isnan(_standardParallel1) && std::isnan(_standardParallel2);}

	private:
		double _latitudeOrigin;
		double _longitudeOrigin;
		double _scale;
		double _falseEasting;
		double _falseNorthing;
		double _standardParallel1;
		double _standardParallel2;
	};

	class Method {
	public:
		Method() : _id(0) {}
		Method(int id);

		int id() const {return _id;}
		bool isNull() const {return (_id == 0);}
		bool isValid() const {return !isNull();}
	private:
		int _id;
	};

	virtual ~Projection() {}

	virtual QPointF ll2xy(const Coordinates &c) const = 0;
	virtual Coordinates xy2ll(const QPointF &p) const = 0;

	static Projection *projection(const Datum &datum, const Method &method,
	  const Setup &setup);
};

QDebug operator<<(QDebug dbg, const Projection::Setup &setup);
QDebug operator<<(QDebug dbg, const Projection::Method &method);

#endif // PROJECTION_H
