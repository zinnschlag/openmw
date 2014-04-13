
#define FIXED_BIAS 0.00001
#define TRANS_BETWEEN_CASCADES 1

float bilinearSample(shTexture2D shadowMap, float2 shadowMapPos, float depth, float2 texelSize)
{
    float2 centroidUV = floor(shadowMapPos.xy / texelSize.xy) * texelSize.xy;

    float4 c;
    c.x = (depth <= FIXED_BIAS + shSample(shadowMap, centroidUV + float2(0,0)*texelSize.xy).r) ? 1 : 0;
    c.y = (depth <= FIXED_BIAS + shSample(shadowMap, centroidUV + float2(0,1)*texelSize.xy).r) ? 1 : 0;
    c.z = (depth <= FIXED_BIAS + shSample(shadowMap, centroidUV + float2(1,0)*texelSize.xy).r) ? 1 : 0;
    c.w = (depth <= FIXED_BIAS + shSample(shadowMap, centroidUV + float2(1,1)*texelSize.xy).r) ? 1 : 0;

#if !SH_GLSL
    float2 weight = frac(shadowMapPos.xy / texelSize.xy);
#else
    float2 weight = fract(shadowMapPos.xy / texelSize.xy);
#endif

    c.x = shLerp(shLerp(c.x, c.y, weight.y), shLerp(c.z, c.w, weight.y), weight.x);
    return c.x;
}

float depthShadowPCF (shTexture2D shadowMap, float4 shadowMapPos, float2 offset)
{
    shadowMapPos /= shadowMapPos.w;
    float3 o = float3(offset.xy, -offset.x) * 0.3;
    
    float c =   (shadowMapPos.z <= FIXED_BIAS + shSample(shadowMap, shadowMapPos.xy - o.xy).r) ? 1 : 0; // top left
    c +=        (shadowMapPos.z <= FIXED_BIAS + shSample(shadowMap, shadowMapPos.xy + o.xy).r) ? 1 : 0; // bottom right
    c +=        (shadowMapPos.z <= FIXED_BIAS + shSample(shadowMap, shadowMapPos.xy + o.zy).r) ? 1 : 0; // bottom left
    c +=        (shadowMapPos.z <= FIXED_BIAS + shSample(shadowMap, shadowMapPos.xy - o.zy).r) ? 1 : 0; // top right
    return c / 4;
}

float depthShadowPCF16 (shTexture2D shadowMap, float4 shadowMapPos, float2 offset)
{
    shadowMapPos /= shadowMapPos.w;

    float sum;
	
    sum  = bilinearSample(shadowMap, shadowMapPos.xy + offset.xy * float2(0, 0), shadowMapPos.z, offset);
    sum += bilinearSample(shadowMap, shadowMapPos.xy + offset.xy * float2(0, 1), shadowMapPos.z, offset);
    sum += bilinearSample(shadowMap, shadowMapPos.xy + offset.xy * float2(1, 0), shadowMapPos.z, offset);
    sum += bilinearSample(shadowMap, shadowMapPos.xy + offset.xy * float2(1, 1), shadowMapPos.z, offset);

    return sum*0.25;
}

// uses only 9 shadowmap fetches instead of 16 for equal result
float depthShadowPCF16_optimised (shTexture2D shadowMap, float4 shadowMapPos, float2 texelSize)
{
	float2 centroidUV = floor(shadowMapPos.xy / texelSize.xy) * texelSize.xy;
	
#if !SH_GLSL
    float2 weight = frac(shadowMapPos.xy / texelSize.xy);
#else
    float2 weight = fract(shadowMapPos.xy / texelSize.xy);
#endif
	
	float sum;
	
	float4 c;
	c.x = shSample(shadowMap, centroidUV + float2(0,0)*texelSize.xy).r;
	c.y = shSample(shadowMap, centroidUV + float2(0,1)*texelSize.xy).r;
    c.z = shSample(shadowMap, centroidUV + float2(1,0)*texelSize.xy).r;
    c.w = shSample(shadowMap, centroidUV + float2(1,1)*texelSize.xy).r;
	c = step(c.xyzw + FIXED_BIAS, shadowMapPos.zzzz).xyzw;

	//top-left pixel bilinear sample
	sum = shLerp(shLerp(c.x, c.y, weight.y), shLerp(c.z, c.w, weight.y), weight.x);
	
	float2 c2;
	c2.x = shSample(shadowMap, centroidUV + float2(2,0)*texelSize.xy).r;
	c2.y = shSample(shadowMap, centroidUV + float2(2,1)*texelSize.xy).r;
	c2 = step(c2.xy + FIXED_BIAS, shadowMapPos.zz).xy;
	
	//top-right
	sum += shLerp(shLerp(c.z, c.w, weight.y), shLerp(c2.x, c2.y, weight.y), weight.x);
	
	float2 c3;
	c3.x = shSample(shadowMap, centroidUV + float2(1,2)*texelSize.xy).r;
	c3.y = shSample(shadowMap, centroidUV + float2(2,2)*texelSize.xy).r;
	c3 = step(c3.xy + FIXED_BIAS, shadowMapPos.zz).xy;
	
	//bottom-right
	sum += shLerp(shLerp(c.w, c3.x, weight.y), shLerp(c2.y, c3.y, weight.y), weight.x);
	
	c.x = shSample(shadowMap, centroidUV + float2(0,2)*texelSize.xy).r;
	c.x = step(c.x + FIXED_BIAS, shadowMapPos.z);
	
	//bottom-left
	sum += shLerp(shLerp(c.y, c.x, weight.y), shLerp(c.w, c3.x, weight.y), weight.x);
	
	return 1.0 - sum*0.25;
}

float shadowWithTransition(shTexture2D shadowMap, float4 shadowMapPos, shTexture2D shadowMapNext, float4 shadowMapPosNext, float2 offset, float trans)
{
	if(trans > 0.0)
	{
		float shadow1 = depthShadowPCF16_optimised(shadowMap, shadowMapPos, offset);
		float shadow2 = depthShadowPCF16_optimised(shadowMapNext, shadowMapPosNext, offset);
		return shLerp(shadow1, shadow2, trans);
	}
	else return depthShadowPCF16_optimised(shadowMap, shadowMapPos, offset);
}



float pssmDepthShadow (


    float4 lightSpacePos0,
    float2 invShadowmapSize0,
    shTexture2D shadowMap0,
    
    float4 lightSpacePos1,
    float2 invShadowmapSize1,
    shTexture2D shadowMap1,
    
    float4 lightSpacePos2,
    float2 invShadowmapSize2,
    shTexture2D shadowMap2,
    
    float depth,
    float3 pssmSplitPoints)

{
    float shadow;
	
#ifndef TRANS_BETWEEN_CASCADES
    if (depth <= pssmSplitPoints.x)
        shadow = depthShadowPCF16(shadowMap0, lightSpacePos0, invShadowmapSize0);
    else if (depth <= pssmSplitPoints.y)
        shadow = depthShadowPCF16(shadowMap1, lightSpacePos1, invShadowmapSize1);
    else
        shadow = depthShadowPCF16(shadowMap2, lightSpacePos2, invShadowmapSize2);
		
#else // smooth transitions between cascades; for transition region there are 2 * (PCF size) fetches
	if (depth <= pssmSplitPoints.x)
	{
		float trans = max(depth/pssmSplitPoints.x - 0.9, 0.0) * 10;
		shadow = shadowWithTransition(shadowMap0, lightSpacePos0, shadowMap1, lightSpacePos1, invShadowmapSize0, trans);
	}
    else if (depth <= pssmSplitPoints.y)
    {
		float trans = max(depth/pssmSplitPoints.y - 0.9, 0.0) * 10;
		shadow = shadowWithTransition(shadowMap1, lightSpacePos1, shadowMap2, lightSpacePos2, invShadowmapSize1, trans);
	}
    else
        shadow = depthShadowPCF16_optimised(shadowMap2, lightSpacePos2, invShadowmapSize2);
#endif
    return shadow;
}
