#version 330 core

out vec4 FragColor;

// 用于计算漫反射
in vec3 normal;// 顶点法向量
in vec3 fragPos;// 顶点位置
uniform vec3 u_lightPos;// 光源位置

// 用于计算镜面反射
uniform vec3 u_viewPos;// 观察位置

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

void main(){
    float ambientStrength = 0.1;// 环境光强度
    vec3 ambient = ambientStrength * u_lightColor;// 环境光

    vec3 norm = normalize(normal);// 先归一化法向量

    // 计算漫反射
    vec3 lightDir = normalize(u_lightPos - fragPos);// 计算光线方向
    // 对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫发射影响
    float diff = max(dot(norm, lightDir), 0.0f);
//    float diff = dot(norm, lightDir);
    // 再乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小：
    vec3 diffuse = u_lightColor * diff;

    // 计算镜面反射
    float specularStrength = 10;// 镜面反射强度
    vec3 viewDir = normalize(u_viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 result = (ambient + diffuse + specular) * u_objectColor;// 计算真实的颜色
    FragColor = vec4(result, 1.0f);
}
