/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: srs-info.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "srs-info.pb-c.h"
void   protocol__nr__srs__iq__est__init
                     (Protocol__NRSRSIQEST         *message)
{
  static const Protocol__NRSRSIQEST init_value = PROTOCOL__NR__SRS__IQ__EST__INIT;
  *message = init_value;
}
size_t protocol__nr__srs__iq__est__get_packed_size
                     (const Protocol__NRSRSIQEST *message)
{
  assert(message->base.descriptor == &protocol__nr__srs__iq__est__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protocol__nr__srs__iq__est__pack
                     (const Protocol__NRSRSIQEST *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protocol__nr__srs__iq__est__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protocol__nr__srs__iq__est__pack_to_buffer
                     (const Protocol__NRSRSIQEST *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protocol__nr__srs__iq__est__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Protocol__NRSRSIQEST *
       protocol__nr__srs__iq__est__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Protocol__NRSRSIQEST *)
     protobuf_c_message_unpack (&protocol__nr__srs__iq__est__descriptor,
                                allocator, len, data);
}
void   protocol__nr__srs__iq__est__free_unpacked
                     (Protocol__NRSRSIQEST *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protocol__nr__srs__iq__est__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   protocol__channle__est__init
                     (Protocol__CHANNLEEST         *message)
{
  static const Protocol__CHANNLEEST init_value = PROTOCOL__CHANNLE__EST__INIT;
  *message = init_value;
}
size_t protocol__channle__est__get_packed_size
                     (const Protocol__CHANNLEEST *message)
{
  assert(message->base.descriptor == &protocol__channle__est__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t protocol__channle__est__pack
                     (const Protocol__CHANNLEEST *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &protocol__channle__est__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t protocol__channle__est__pack_to_buffer
                     (const Protocol__CHANNLEEST *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &protocol__channle__est__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Protocol__CHANNLEEST *
       protocol__channle__est__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Protocol__CHANNLEEST *)
     protobuf_c_message_unpack (&protocol__channle__est__descriptor,
                                allocator, len, data);
}
void   protocol__channle__est__free_unpacked
                     (Protocol__CHANNLEEST *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &protocol__channle__est__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor protocol__nr__srs__iq__est__field_descriptors[1] =
{
  {
    "CHANNLE_EST_LIST",
    4,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Protocol__NRSRSIQEST, n_channle_est_list),
    offsetof(Protocol__NRSRSIQEST, channle_est_list),
    &protocol__channle__est__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protocol__nr__srs__iq__est__field_indices_by_name[] = {
  0,   /* field[0] = CHANNLE_EST_LIST */
};
static const ProtobufCIntRange protocol__nr__srs__iq__est__number_ranges[1 + 1] =
{
  { 4, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor protocol__nr__srs__iq__est__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protocol.NR_SRS_IQ_EST",
  "NRSRSIQEST",
  "Protocol__NRSRSIQEST",
  "protocol",
  sizeof(Protocol__NRSRSIQEST),
  1,
  protocol__nr__srs__iq__est__field_descriptors,
  protocol__nr__srs__iq__est__field_indices_by_name,
  1,  protocol__nr__srs__iq__est__number_ranges,
  (ProtobufCMessageInit) protocol__nr__srs__iq__est__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor protocol__channle__est__field_descriptors[2] =
{
  {
    "image",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Protocol__CHANNLEEST, image),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "real",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Protocol__CHANNLEEST, real),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned protocol__channle__est__field_indices_by_name[] = {
  0,   /* field[0] = image */
  1,   /* field[1] = real */
};
static const ProtobufCIntRange protocol__channle__est__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor protocol__channle__est__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "protocol.CHANNLE_EST",
  "CHANNLEEST",
  "Protocol__CHANNLEEST",
  "protocol",
  sizeof(Protocol__CHANNLEEST),
  2,
  protocol__channle__est__field_descriptors,
  protocol__channle__est__field_indices_by_name,
  1,  protocol__channle__est__number_ranges,
  (ProtobufCMessageInit) protocol__channle__est__init,
  NULL,NULL,NULL    /* reserved[123] */
};
