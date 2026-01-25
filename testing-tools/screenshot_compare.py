#!/usr/bin/env python3
"""
Screenshot Comparison Tool for MFC vs wxWidgets W3DView
Compares screenshots pixel-by-pixel and generates difference reports.
"""

import os
import sys
from PIL import Image, ImageChops, ImageDraw, ImageFont
import argparse

def compare_images(image1_path, image2_path, output_path=None, tolerance=5):
    """
    Compare two images and generate a difference visualization.
    
    Args:
        image1_path: Path to first image (MFC)
        image2_path: Path to second image (wxWidgets)
        output_path: Optional path to save difference image
        tolerance: Pixel difference tolerance (0-255)
    
    Returns:
        dict with comparison results
    """
    try:
        img1 = Image.open(image1_path).convert('RGB')
        img2 = Image.open(image2_path).convert('RGB')
    except Exception as e:
        return {'error': f"Failed to load images: {e}"}
    
    # Check if sizes match
    if img1.size != img2.size:
        return {
            'match': False,
            'error': f"Size mismatch: {img1.size} vs {img2.size}",
            'size_difference': True
        }
    
    # Calculate pixel-by-pixel difference
    diff = ImageChops.difference(img1, img2)
    
    # Convert difference to grayscale for analysis
    diff_gray = diff.convert('L')
    pixels = list(diff_gray.getdata())
    
    # Count different pixels based on tolerance
    different_pixels = sum(1 for p in pixels if p > tolerance)
    total_pixels = len(pixels)
    difference_percentage = (different_pixels / total_pixels) * 100
    
    # Generate difference visualization if output path provided
    if output_path:
        # Create red overlay for differences
        diff_vis = Image.new('RGB', img1.size)
        for i, (pix1, pix2) in enumerate(zip(img1.getdata(), img2.getdata())):
            if sum(abs(a - b) for a, b in zip(pix1, pix2)) > tolerance * 3:
                # Highlight differences in red
                diff_vis.putpixel((i % img1.width, i // img1.width), (255, 0, 0))
            else:
                # Show original pixel
                diff_vis.putpixel((i % img1.width, i // img1.width), pix1)
        
        # Create side-by-side comparison
        comparison = Image.new('RGB', (img1.width * 3, img1.height))
        comparison.paste(img1, (0, 0))
        comparison.paste(img2, (img1.width, 0))
        comparison.paste(diff_vis, (img1.width * 2, 0))
        
        # Add labels
        draw = ImageDraw.Draw(comparison)
        try:
            font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 20)
        except:
            font = ImageFont.load_default()
        
        draw.text((10, 10), "MFC Original", fill=(255, 255, 0), font=font)
        draw.text((img1.width + 10, 10), "wxWidgets", fill=(0, 255, 255), font=font)
        draw.text((img1.width * 2 + 10, 10), "Differences", fill=(255, 0, 0), font=font)
        
        comparison.save(output_path)
    
    # Determine if match based on tolerance
    match = difference_percentage < 1.0  # Less than 1% difference
    
    return {
        'match': match,
        'different_pixels': different_pixels,
        'total_pixels': total_pixels,
        'difference_percentage': difference_percentage,
        'tolerance': tolerance,
        'size': img1.size
    }

def main():
    parser = argparse.ArgumentParser(description='Compare MFC and wxWidgets screenshots')
    parser.add_argument('mfc_image', help='Path to MFC screenshot')
    parser.add_argument('wx_image', help='Path to wxWidgets screenshot')
    parser.add_argument('-o', '--output', help='Output path for difference image')
    parser.add_argument('-t', '--tolerance', type=int, default=5, 
                        help='Pixel difference tolerance (0-255, default: 5)')
    parser.add_argument('-v', '--verbose', action='store_true', 
                        help='Verbose output')
    
    args = parser.parse_args()
    
    result = compare_images(args.mfc_image, args.wx_image, args.output, args.tolerance)
    
    if 'error' in result:
        print(f"ERROR: {result['error']}")
        return 1
    
    if args.verbose:
        print(f"Image Size: {result['size']}")
        print(f"Total Pixels: {result['total_pixels']}")
        print(f"Different Pixels: {result['different_pixels']}")
        print(f"Difference: {result['difference_percentage']:.2f}%")
        print(f"Tolerance: {result['tolerance']}")
    
    if result['match']:
        print("✅ MATCH: Images are similar (within tolerance)")
        return 0
    else:
        print(f"❌ DIFFERENT: {result['difference_percentage']:.2f}% pixels differ")
        if args.output:
            print(f"Difference visualization saved to: {args.output}")
        return 1

if __name__ == '__main__':
    sys.exit(main())
