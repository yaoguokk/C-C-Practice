#ifndef KAFKACONSUMER_H
#define KAFKACONSUMER_H

#include "librdkafka/rdkafka.h"
 #include <inttypes.h>
 
typedef void (* consumer_callback)(rd_kafka_message_t *rkmessage, void *opaque);
 
 
class CKafkaConsumer
{
public:
	rd_kafka_t *                         m_kafka_handle;  //kafka消息生产者句柄
	rd_kafka_topic_t *                   m_kafka_topic;   //kafka消息主题名称
	rd_kafka_conf_t *                    m_kafka_conf;    //kafka消息配置
	rd_kafka_topic_conf_t *              m_kafka_topic_conf;
	rd_kafka_topic_partition_list_t *    m_kafka_topic_partition_list;
	rd_kafka_queue_t *                   m_kafka_queue;
 
	consumer_callback                    m_consumer_callback; //消息回调函数
	void *                               m_consumer_callback_param; //消息回调函数的参数
 
public:
	CKafkaConsumer();
	~CKafkaConsumer();
 
	int init(char *topic, char *brokers, char *partitions, char *groupId, consumer_callback consumer_cb, void * param_cb); //topic="my_test"; brokers="192.168.1.42:9092"; partitions="0,1,2"; groupId="my_group";
	int getMessage(); //从kafka服务器接收消息
 
	static void err_cb(rd_kafka_t *rk, int err, const char *reason, void *opaque);
	static void throttle_cb(rd_kafka_t *rk, const char *broker_name, int32_t broker_id, int throttle_time_ms, void *opaque);
	static void offset_commit_cb(rd_kafka_t *rk, rd_kafka_resp_err_t err, rd_kafka_topic_partition_list_t *offsets, void *opaque);
	static int stats_cb(rd_kafka_t *rk, char *json, size_t json_len, void *opaque);
	static void logger(const rd_kafka_t *rk, int level, const char *fac, const char *buf);
	static void msg_consume(rd_kafka_message_t *rkmessage, void *opaque);

};

#endif