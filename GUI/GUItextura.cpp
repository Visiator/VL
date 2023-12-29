/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <fstream>
#include <iostream>
#include <memory>

#include "GUItextura.h"

int buf_fread(void *val, size_t sz, std::vector<uint8_t>buffer, size_t read_all)
{
    uint8_t* v = (uint8_t *)val;
    size_t i = 0;
    for (i = 0; i < sz && i+read_all < buffer.size(); i++)
    {
        v[i] = buffer[read_all + i];
    }
    return i;
}

void GUItextura::load_from_buffer(std::vector<uint8_t>buffer)
{
    int read_sz, read_all = 0;
    _BMP_header_part1 head1;
    _BMP_header_part2 head2;
    uint8_t b3[3];

    //using unique_file_t = std::unique_ptr<FILE, decltype(&std::fclose)>;

    //unique_file_t fi(std::fopen(name, "rb"), &std::fclose);


    read_sz = buf_fread(&head1, sizeof(head1), buffer, read_all);

    if (read_sz != sizeof(head1)) {
        return;
    }
    read_all += read_sz;
    if (head1.bitmapinfo_ver != 40) {
        return;
    }
    read_sz = buf_fread(&head2, sizeof(head2), buffer, read_all);
    if (read_sz != sizeof(head2)) {
        return;
    }
    read_all += read_sz;
    if (read_all != head1.offBits) {
        return;
    }
    
    if (head2.compression == 0 && head2.bitcount == 24)
    {
        if (head1.size - head1.offBits == head2.sizeimage)
        {
            //int i = head1.offBits;
BEGIN_ATTRIBUTE_PACKED
            union _rgb_ {
                uint8_t b[4];
                uint32_t rgb;
            };
END_ATTRIBUTE_PACKED
            int idx = 0, idx_max = head2.width * head2.height;
            buf.resize(idx_max);
            w = head2.width;
            h = head2.height;
            _rgb_ clr;
            for (int y = head2.height - 1; y >= 0; y--)
            {
                int j = 0;
                idx = y * head2.width;
                for (size_t x = 0; x < head2.width; x++)
                {
                    read_sz = buf_fread(&b3[0], 3, buffer, read_all);
                    if (read_sz != 3)
                    {
                        return;
                    }
                    read_all += read_sz;
                    clr.b[0] = b3[0];
                    clr.b[1] = b3[1];
                    clr.b[2] = b3[2];
                    clr.b[3] = 0;
                    if (idx >= idx_max)
                    {
                        return;
                    }
                    buf[idx++] = clr.rgb;
                    //i += 3;
                    j += 3;
                }
                j = head2.width % 4;
                if (j > 0)
                {
                    read_sz = buf_fread(&b3[0], j, buffer, read_all);
                    if (read_sz != j)
                    {
                        return;
                    }
                    read_all += read_sz;
                }
                //i += j;
            }
            return;
        }
        else {
            // error
        }
        return;
    }
    
}

void GUItextura::load_from_file(std::string name_file) {
    //////////////////////////////
    std::string name;
    int idx, w, h;
    std::ifstream fstFile;

    name = "inc/" + name_file;
    fstFile.open(name.c_str(), std::ios::binary);
    if (!fstFile.is_open())
    {
        name = "../inc/" + name_file;
        fstFile.open(name.c_str(), std::ios::binary);
    }
    if (fstFile.is_open())
    {
        fstFile.seekg(0, std::ios_base::end);
        int len = fstFile.tellg();
        fstFile.seekg(0, std::ios_base::beg);
        std::vector<uint8_t>buf;
        buf.clear();
        buf.resize(len);
        fstFile.read((char*)buf.data(), len);
        if (fstFile.gcount() == len) {
            fstFile.close();
            load_from_buffer(buf);
        }
        else {
            fstFile.close();
        }
    }
    //////////////////////////////
    
}

GUItextura* GUItexturaList::get_textura_by_id(const char *id) {
    for(size_t i = 0; i < items.size(); i++) {
        if(items[i].id == id) {
            return &items[i];
        }
    }
    return nullptr;
}