#ifndef _048_Colors_h
#define _048_Colors_h

typedef struct TColor
{
    float r;
    float g;
    float b;
    float a;
    
} Color;

Color colors[15];
Color text_colors[15];

void InitColors();
void AddColor(int index, Color color);
void AddTextColor(int index, Color color);

Color ResurnColor(float r, float g, float b, float a)
{
    Color result;
    result.a = a;
    result.r = r;
    result.b = b;
    result.g = g;
    return result;
}

void InitColors()
{
    AddColor(0,ResurnColor(200, 77, 194, 255));
    AddColor(1,ResurnColor(238, 228, 218, 255));  //     2
    AddColor(2,ResurnColor(255, 229, 180, 255));  //     4
    AddColor(3,ResurnColor(251, 174, 114, 255));  //     8
    AddColor(4,ResurnColor(253, 140, 87, 255));   //    16
    AddColor(5,ResurnColor(255, 108, 83, 255));   //    32
    AddColor(6,ResurnColor(255, 64, 30, 255));    //    64
    AddColor(7,ResurnColor(239, 209, 106, 255));  //   128
    AddColor(8,ResurnColor(240, 207, 86, 255));   //   256
    AddColor(9,ResurnColor(240, 203, 65, 255));   //   512
    AddColor(10,ResurnColor(250, 197, 41, 255)); //  1024
    AddColor(11,ResurnColor(243, 178, 39, 255));   //  2048
    AddColor(12,ResurnColor(88, 214, 127, 255));   //  4096

    
    AddTextColor(0,ResurnColor(255, 255, 255, 255));
    AddTextColor(1,ResurnColor(0, 0, 0, 255));  //     2
    AddTextColor(2,ResurnColor(0, 0, 0, 255));  //     4
    AddTextColor(3,ResurnColor(255, 255, 255, 255));  //     8
    AddTextColor(4,ResurnColor(255, 255, 255, 255));  //    16
    AddTextColor(5,ResurnColor(255, 255, 255, 255));  //    32
    AddTextColor(6,ResurnColor(255, 255, 255, 255));  //    64
    AddTextColor(7,ResurnColor(255, 255, 255, 255));  //   128
    AddTextColor(8,ResurnColor(255, 255, 255, 255));  //   256
    AddTextColor(9,ResurnColor(255, 255, 255, 255));  //   512
    AddTextColor(10,ResurnColor(255, 255, 255, 255)); //  1024
    AddTextColor(11,ResurnColor(255, 255, 255, 255)); //  2048
    AddTextColor(12,ResurnColor(255, 255, 255, 255)); //  4096


}

void AddColor(int index, Color color)
{
    colors[index].r =  color.r/255;
    colors[index].g =  color.g/255;
    colors[index].b =  color.b/255;
    colors[index].a =  color.a/255;
}

void AddTextColor(int index, Color color)
{
    text_colors[index].r =  color.r/255;
    text_colors[index].g =  color.g/255;
    text_colors[index].b =  color.b/255;
    text_colors[index].a =  color.a/255;
}

Color GetColor(int value)
{
    switch (value)
    {
        case 2:  return colors[1]; break;
        case 4:  return colors[2]; break;
        case 8:  return colors[3]; break;
        case 16: return colors[4]; break;
        case 32: return colors[5]; break;
        case 64: return colors[6]; break;
        case 128: return colors[7]; break;
        case 256: return colors[8]; break;
        case 512: return colors[9]; break;
        case 1024: return colors[10]; break;
        case 2048: return colors[11]; break;
        case 4096: return colors[12]; break;
        default: return colors[6]; break;
    }
}

Color GetTextColor(int value)
{
    switch (value)
    {
        case 2:  return text_colors[1]; break;
        case 4:  return text_colors[2]; break;
        case 8:  return text_colors[3]; break;
        case 16: return text_colors[4]; break;
        case 32: return text_colors[5]; break;
        case 64: return text_colors[6]; break;
        case 128: return text_colors[7]; break;
        case 256: return text_colors[8]; break;
        case 512: return text_colors[9]; break;
        case 1024: return text_colors[10]; break;
        case 2048: return text_colors[11]; break;
        case 4096: return text_colors[12]; break;
        default: return text_colors[6]; break;
    }
}

#endif