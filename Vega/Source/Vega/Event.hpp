#ifndef VEGA_EVENT_HPP
#define VEGA_EVENT_HPP

namespace Vega {
  class Event final {
  public:
    explicit Event() = default;

    virtual ~Event() = default;
  };
}

#endif