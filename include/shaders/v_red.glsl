uniform mat4 u_mvp;                 
attribute vec4 a_position;                
attribute vec3 a_color;                   
varying lowp vec4 v_color;                

void main()                               
{                                         
   v_color.xyz = a_color;                 
   v_color.w = 1.0;                       
   gl_Position = u_mvp * a_position;
}                                         

