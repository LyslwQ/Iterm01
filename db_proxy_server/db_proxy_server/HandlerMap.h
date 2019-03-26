#ifndef HANDLERMAP_H_
#define HANDLERMAP_H_


#include "ProxyTask.h"
#include "../base/util.h"

typedef map<uint32_t, pdu_handler_t> HandlerMap_t;

class CHandlerMap {
public:
  virtual ~CHandlerMap();

  static CHandlerMap* getInstance();

  void Init();
  bool GetHandler(uint32_t pdu_type, pdu_handler_t& handler);
private:
  CHandlerMap();

private:
  static  CHandlerMap* s_handler_instance;

  HandlerMap_t 	m_handler_map;
};

#endif /* HANDLERMAP_H_ */
