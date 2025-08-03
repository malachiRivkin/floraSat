"""
Decode protobuf messages
"""

#dependencies
import plantSat_pb2
import csv

#test data
test_data_hex = "08DEC6B8C406151353C7411D74677F442557488F422D67F88241"
bulk_data_hex = 'plantSat_dataOut.bin'


def plantSat_get_fieldnames():
    message_descriptor = plantSat_pb2.SimpleMessage.DESCRIPTOR
    field_descriptors = message_descriptor.fields
    fields = []
    for field in field_descriptors:
        fields.append(field.name)
    return fields


def plantSat_decode_message(MESSAGE):
    test_data = bytes.fromhex(MESSAGE)
    message = plantSat_pb2.SimpleMessage()
    #decode_file(bulk_data_hex)
    message.ParseFromString(test_data)
    values = []
    for field, value in message.ListFields():
        values.append(value)

    return values


def plantSat_decode_file(FILE):
    
    fname_out = FILE.split('.')[0] + '.csv'
    print("fnameOut: ",fname_out)
    fields = plantSat_get_fieldnames()
    #add header containing field names to output file
    with open(fname_out, 'w', newline='') as outfile:
        writer = csv.writer(outfile, delimiter=',')
        writer.writerow(fields)

    with open(bulk_data_hex, 'r') as infile:

        for line in infile:
            line_data = plantSat_decode_message(line)
            with open(fname_out, 'a', newline='') as outfile:
                writer = csv.writer(outfile)
                writer.writerow(line_data)
                    


#message = plantSat_pb2.SimpleMessage()
#decode_file(bulk_data_hex)
#message.ParseFromString(test_data)

#data = plantSat_decode_message(test_data_hex)
#print(data)

plantSat_decode_file(bulk_data_hex)


